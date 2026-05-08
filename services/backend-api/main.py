import asyncio
import json
import logging
import os
from contextlib import asynccontextmanager
from datetime import datetime
from typing import Any, Dict, List, cast

import aio_pika
import psycopg2
import requests
import uvicorn
from dotenv import load_dotenv
from fastapi import (
    Depends,
    FastAPI,
    HTTPException,
    Query,
    Security,
    WebSocket,
    WebSocketDisconnect,
    status,
)
from fastapi.middleware.cors import CORSMiddleware
from fastapi.security import HTTPBearer
from jose import JWTError, jwt
from psycopg2.extras import RealDictCursor
from pydantic import BaseModel
from pymongo import MongoClient

load_dotenv()

POSTGRES_HOST = os.environ.get("POSTGRES_HOST", "localhost")
POSTGRES_PORT = os.environ.get("POSTGRES_PORT", "5432")
POSTGRES_USERNAME = os.environ.get("POSTGRES_USERNAME", "admin")
POSTGRES_PASSWORD = os.environ.get("POSTGRES_PASSWORD", "admin")
POSTGRES_NAME = os.environ.get("POSTGRES_NAME", "default_db")

MONGODB_HOST = os.environ.get("MONGODB_HOST", "localhost")
MONGODB_PORT = os.environ.get("MONGODB_PORT", "27017")
MONGODB_USERNAME = os.environ.get("MONGODB_USERNAME", "admin")
MONGODB_PASSWORD = os.environ.get("MONGODB_PASSWORD", "admin")
MONGODB_DB = os.environ.get("MONGODB_DB", "default_db")

RABBITMQ_HOST = os.environ.get("RABBITMQ_HOST", "localhost")
RABBITMQ_PORT = int(os.environ.get("RABBITMQ_PORT", "5672"))
RABBITMQ_USERNAME = os.environ.get("RABBITMQ_USERNAME", "admin")
RABBITMQ_PASSWORD = os.environ.get("RABBITMQ_PASSWORD", "admin")

KEYCLOAK_PG_HOST = os.environ.get("KEYCLOAK_PG_HOST", "localhost")
KEYCLOAK_PG_PORT = os.environ.get("KEYCLOAK_PG_PORT", "5433")
KEYCLOAK_PG_USERNAME = os.environ.get("KEYCLOAK_PG_USERNAME", "admin")
KEYCLOAK_PG_PASSWORD = os.environ.get("KEYCLOAK_PG_PASSWORD", "admin")
KEYCLOAK_PG_NAME = os.environ.get("KEYCLOAK_PG_NAME", "keycloak_db")

KEYCLOAK_CERTS_URL = os.environ.get(
    "KEYCLOAK_CERTS_URL",
    "https://auth.260824.xyz/realms/solartracker/protocol/openid-connect/certs",
)

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S",
)

logger = logging.getLogger("backend-api")

logging.getLogger("fastapi").setLevel(logging.ERROR)
logging.getLogger("uvicorn").setLevel(logging.ERROR)
logging.getLogger("uvicorn.access").setLevel(logging.ERROR)
logging.getLogger("uvicorn.error").setLevel(logging.ERROR)
logging.getLogger("aio_pika").setLevel(logging.ERROR)

security = HTTPBearer()


def verify_token_logic(token):
    try:
        jwks_response = requests.get(KEYCLOAK_CERTS_URL, timeout=5)
        jwks_response.raise_for_status()
        jwks = jwks_response.json()

        payload = jwt.decode(
            token, jwks, algorithms=["RS256"], options={"verify_aud": False}
        )
        return payload
    except JWTError as e:
        logger.error(f"JWT Verification failed: {e}")
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED, detail="Invalid token"
        )
    except Exception as e:
        logger.error(f"Auth server error: {e}")
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail="Auth server unavailable",
        )


def verify_rest_token(credentials=Security(security)):
    return verify_token_logic(credentials.credentials)


def get_postgres_connection():
    try:
        conn = psycopg2.connect(
            host=POSTGRES_HOST,
            port=POSTGRES_PORT,
            user=POSTGRES_USERNAME,
            password=POSTGRES_PASSWORD,
            dbname=POSTGRES_NAME,
            cursor_factory=RealDictCursor,
        )
        return conn
    except Exception as e:
        logger.error(f"Database connection failed: {e}.")
        raise HTTPException(status_code=500, detail="Database connection error")


def get_keycloak_pg_connection():
    try:
        conn = psycopg2.connect(
            host=KEYCLOAK_PG_HOST,
            port=KEYCLOAK_PG_PORT,
            user=KEYCLOAK_PG_USERNAME,
            password=KEYCLOAK_PG_PASSWORD,
            dbname=KEYCLOAK_PG_NAME,
            cursor_factory=RealDictCursor,
        )
        return conn
    except Exception as e:
        logger.error(f"Database connection failed: {e}.")
        raise HTTPException(status_code=500, detail="Database connection error")


def get_mongodb_client():
    uri = f"mongodb://{MONGODB_USERNAME}:{MONGODB_PASSWORD}@{MONGODB_HOST}:{MONGODB_PORT}/"
    return MongoClient(uri)


async def consume_rabbitmq(manager):
    while True:
        try:
            connection = await aio_pika.connect_robust(
                host=RABBITMQ_HOST,
                port=RABBITMQ_PORT,
                login=RABBITMQ_USERNAME,
                password=RABBITMQ_PASSWORD,
            )

            async with connection:
                channel = await connection.channel()

                exchange = await channel.declare_exchange(
                    name="processed_telemetry",
                    type=aio_pika.ExchangeType.TOPIC,
                    durable=True,
                )

                queue = await channel.declare_queue(exclusive=True, auto_delete=True)
                await queue.bind(exchange, routing_key="processed.#")

                async with queue.iterator() as queue_iter:
                    async for message in queue_iter:
                        async with message.process():
                            payload = json.loads(message.body.decode())

                            routing_key = str(message.routing_key)
                            device_id = routing_key.split(".")[-1]

                            if routing_key.startswith("processed.telemetry."):
                                payload["type"] = "live_telemetry"

                            await manager.broadcast_to_device(device_id, payload)

        except Exception as e:
            logger.error(f"RabbitMQ consumer error: {e}. Retrying in 5 seconds...")
            await asyncio.sleep(5)


def get_user_allowed_device_ids(user_data):
    user_id = user_data.get("sub")

    allowed_device_ids = []

    try:
        conn = get_keycloak_pg_connection()
        with conn.cursor() as cursor:
            cursor.execute(
                """
                SELECT c.device_ids
                FROM users u
                JOIN companies c ON u.company_id = c.id
                WHERE u.id = %s
            """,
                (user_id,),
            )
            result = cast(Dict[str, Any], cursor.fetchone())

            if result and result.get("device_ids"):
                allowed_device_ids = result["device_ids"]
            else:
                logger.info(f"User {user_id} has no assigned company or assets.")
                allowed_device_ids = []
    except Exception as e:
        logger.error(f"PostgreSQL query failed: {str(e)}")
        raise HTTPException(
            status_code=500, detail="Database error during permission check"
        )
    finally:
        if "conn" in locals() and conn:
            conn.close()

    return allowed_device_ids


class ConnectionManager:
    def __init__(self):
        self.active_connections: Dict[str, List[WebSocket]] = {}

    async def connect(self, websocket: WebSocket, device_id: str):
        await websocket.accept()
        if device_id not in self.active_connections:
            self.active_connections[device_id] = []
        self.active_connections[device_id].append(websocket)
        logger.info(
            f"WebSocket connected | Device: {device_id} | Total clients for device: {len(self.active_connections[device_id])}"
        )

    def disconnect(self, websocket, device_id):
        if device_id in self.active_connections:
            self.active_connections[device_id].remove(websocket)
            if not self.active_connections[device_id]:
                del self.active_connections[device_id]
            logger.info(f"WebSocket disconnected | Device: {device_id}")

    async def broadcast_to_device(self, device_id, message):
        if device_id in self.active_connections:
            for connection in self.active_connections[device_id]:
                try:
                    await connection.send_json(message)
                except Exception as e:
                    logger.error(f"Failed to send WS message: {e}")


manager = ConnectionManager()


@asynccontextmanager
async def lifespan(app):
    logger.info("Starting API...")

    asyncio.create_task(consume_rabbitmq(manager))

    yield

    logger.info("Shutting down API...")


app = FastAPI(title="Solar Tracker API", version="1.0.0", lifespan=lifespan)

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["GET"],
    allow_headers=["*"],
)


@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(
    device_id: str,
    start_date: datetime = Query(..., description="Start timestamp (ISO 8601)"),
    end_date: datetime = Query(..., description="End timestamp (ISO 8601)"),
    user_data: dict = Depends(verify_rest_token),
):
    logger.info(
        f"Fetching telemetry for {device_id} | Range: {start_date} to {end_date}."
    )

    try:
        allowed_device_ids = get_user_allowed_device_ids(user_data)
    except Exception as e:
        logger.error(f"Error occurred while fetching allowed asset IDs: {e}")
        raise HTTPException(status_code=500, detail="Internal Server Error")

    if device_id not in allowed_device_ids:
        logger.warning(
            f"Unauthorized access attempt to device {device_id} by user {user_data.get('sub')}."
        )
        raise HTTPException(
            status_code=403, detail="Forbidden: You don't have access to this device"
        )

    conn = get_postgres_connection()
    try:
        with conn.cursor() as cursor:
            query = """
                    SELECT time, (voltage_v * current_a) AS power_w, irradiance_wm2, temp_c, yaw_angle_deg, status
                    FROM telemetry
                    WHERE device_id = %s
                      AND time >= %s
                      AND time <= %s
                    ORDER BY time ASC; \
                    """
            cursor.execute(query, (device_id, start_date, end_date))
            results = cursor.fetchall()

            logger.info(f"Query successful. Found {len(results)} records.")
            return {"device_id": device_id, "data": results}
    finally:
        conn.close()


@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(
    device_id: str,
    start_date: datetime = Query(..., description="Start timestamp (ISO 8601)"),
    end_date: datetime = Query(..., description="End timestamp (ISO 8601)"),
    user_data: dict = Depends(verify_rest_token),
):
    logger.info(
        f"Fetching forecast for {device_id} | Range: {start_date} to {end_date}."
    )

    try:
        allowed_device_ids = get_user_allowed_device_ids(user_data)
    except Exception as e:
        logger.error(f"Error occurred while fetching allowed asset IDs: {e}")
        raise HTTPException(status_code=500, detail="Internal Server Error")

    if device_id not in allowed_device_ids:
        logger.warning(
            f"Unauthorized access attempt to device {device_id} by user {user_data.get('sub')}."
        )
        raise HTTPException(
            status_code=403, detail="Forbidden: You don't have access to this device"
        )

    conn = get_postgres_connection()
    try:
        with conn.cursor() as cursor:
            query = """
                    SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                    FROM forecast
                    WHERE device_id = %s
                      AND time >= %s
                      AND time <= %s
                    ORDER BY time ASC; \
                    """
            cursor.execute(query, (device_id, start_date, end_date))
            results = cast(List[Dict[str, Any]], cursor.fetchall())

            if results:
                keys_to_remove = [
                    key
                    for key in results[0].keys()
                    if all(row[key] is None for row in results)
                ]

                if keys_to_remove:
                    for row in results:
                        for key in keys_to_remove:
                            row.pop(key, None)

            logger.info(f"Query successful. Found {len(results)} records.")
            return {"device_id": device_id, "data": results}
    finally:
        conn.close()


@app.get("/api/v1/assets")
def get_all_assets(user_data: dict = Depends(verify_rest_token)):
    logger.info("Fetching all assets from pv_assets and wind_assets.")

    try:
        allowed_device_ids = get_user_allowed_device_ids(user_data)
    except Exception as e:
        logger.error(f"Error occurred while fetching allowed asset IDs: {e}")
        raise HTTPException(status_code=500, detail="Internal Server Error")

    mongo_filter = {"device_id": {"$in": allowed_device_ids}}

    client = get_mongodb_client()

    try:
        db = client[MONGODB_DB]

        pv_cursor = db["assets_pv"].find(mongo_filter, {"_id": 0})
        pv_assets = list(pv_cursor)
        for asset in pv_assets:
            asset["asset_type"] = "pv"

        wind_cursor = db["assets_wind"].find(mongo_filter, {"_id": 0})
        wind_assets = list(wind_cursor)
        for asset in wind_assets:
            asset["asset_type"] = "wind"

        combined_assets = pv_assets + wind_assets
        combined_assets.sort(key=lambda asset: asset.get("farm_name", "").lower())

        logger.info(
            f"Query successful. Found {len(pv_assets)} PV and {len(wind_assets)} Wind assets."
        )
        return combined_assets

    except Exception as e:
        logger.error(f"MongoDB query failed: {str(e)}.")
        raise HTTPException(status_code=500, detail="Failed to fetch assets")

    finally:
        client.close()


class PushTokenUpdate(BaseModel):
    token: str


@app.post("/api/v1/update-push-token")
def update_push_token(
    payload: PushTokenUpdate,
    user_data: dict = Depends(verify_rest_token),
):
    logger.info(f"Updating push token for user {user_data.get('sub')}.")

    user_id = user_data.get("sub")

    try:
        conn = get_keycloak_pg_connection()
        with conn.cursor() as cursor:
            cursor.execute(
                """
                UPDATE users
                SET expo_push_token = %s
                WHERE id = %s
                """,
                (payload.token, user_id),
            )
            conn.commit()

        logger.info("Push token updated successfully.")

    except Exception as e:
        logger.error(f"PostgreSQL query failed: {str(e)}")
        raise HTTPException(
            status_code=500, detail="Database error during permission check"
        )
    finally:
        if "conn" in locals() and conn:
            conn.close()


@app.websocket("/api/v1/ws/live/{device_id}")
async def websocket_live_stream(
    websocket: WebSocket, device_id: str, token: str = Query(...)
):
    try:
        user_data = verify_token_logic(token)
    except Exception as e:
        logger.warning(f"Invalid WS token for device {device_id}: {str(e)}")
        await websocket.close(code=status.WS_1008_POLICY_VIOLATION)
        return

    try:
        allowed_device_ids = get_user_allowed_device_ids(user_data)
    except Exception as e:
        logger.error(f"Failed to fetch permissions for WS: {str(e)}")
        await websocket.close(code=status.WS_1011_INTERNAL_ERROR)
        return

    if device_id not in allowed_device_ids:
        logger.warning(
            f"Unauthorized WS access attempt to device {device_id} by user {user_data.get('sub')}."
        )
        await websocket.close(code=status.WS_1008_POLICY_VIOLATION)
        return

    await manager.connect(websocket, device_id)

    try:
        while True:
            await websocket.receive_text()
    except WebSocketDisconnect:
        manager.disconnect(websocket, device_id)
        logger.info(f"WebSocket disconnected for device {device_id}")


if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8001, log_level="error")