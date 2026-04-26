import asyncio
import json
import logging
import os
from contextlib import asynccontextmanager
from datetime import datetime
from typing import Dict, List

import aio_pika
import psycopg2
from dotenv import load_dotenv
from fastapi import FastAPI, HTTPException, Query, WebSocket, WebSocketDisconnect
from fastapi.middleware.cors import CORSMiddleware
from psycopg2.extras import RealDictCursor
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

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S"
)

logger = logging.getLogger("backend-api")

logging.getLogger("fastapi").setLevel(logging.ERROR)
logging.getLogger("uvicorn").setLevel(logging.ERROR)
logging.getLogger("uvicorn.access").setLevel(logging.ERROR)
logging.getLogger("uvicorn.error").setLevel(logging.ERROR)
logging.getLogger("aio_pika").setLevel(logging.ERROR)


def get_postgres_connection():
    try:
        conn = psycopg2.connect(
            host=POSTGRES_HOST,
            port=POSTGRES_PORT,
            user=POSTGRES_USERNAME,
            password=POSTGRES_PASSWORD,
            dbname=POSTGRES_NAME,
            cursor_factory=RealDictCursor
        )
        return conn
    except Exception as e:
        logger.error(f"Database connection failed: {e}.")
        raise HTTPException(status_code=500, detail="Database connection error")


def get_mongodb_client():
    uri = f"mongodb://{MONGODB_USERNAME}:{MONGODB_PASSWORD}@{MONGODB_HOST}:{MONGODB_PORT}/"
    return MongoClient(uri)


class ConnectionManager:
    def __init__(self):
        self.active_connections: Dict[str, List[WebSocket]] = {}

    async def connect(self, websocket: WebSocket, device_id: str):
        await websocket.accept()
        if device_id not in self.active_connections:
            self.active_connections[device_id] = []
        self.active_connections[device_id].append(websocket)
        logger.info(
            f"WebSocket connected | Device: {device_id} | Total clients for device: {len(self.active_connections[device_id])}")

    def disconnect(self, websocket: WebSocket, device_id: str):
        if device_id in self.active_connections:
            self.active_connections[device_id].remove(websocket)
            if not self.active_connections[device_id]:
                del self.active_connections[device_id]
            logger.info(f"WebSocket disconnected | Device: {device_id}")

    async def broadcast_to_device(self, device_id: str, message: dict):
        if device_id in self.active_connections:
            for connection in self.active_connections[device_id]:
                try:
                    await connection.send_json(message)
                except Exception as e:
                    logger.error(f"Failed to send WS message: {e}")


manager = ConnectionManager()


async def consume_rabbitmq():
    while True:
        try:
            connection = await aio_pika.connect_robust(
                host=RABBITMQ_HOST,
                port=RABBITMQ_PORT,
                login=RABBITMQ_USERNAME,
                password=RABBITMQ_PASSWORD
            )

            async with connection:
                channel = await connection.channel()

                exchange = await channel.declare_exchange(
                    name="processed_telemetry",
                    type=aio_pika.ExchangeType.TOPIC,
                    durable=True
                )

                queue = await channel.declare_queue(exclusive=True, auto_delete=True)
                await queue.bind(exchange, routing_key="processed.#")

                async with queue.iterator() as queue_iter:
                    async for message in queue_iter:
                        async with message.process():
                            payload = json.loads(message.body.decode())

                            routing_key = message.routing_key
                            device_id = routing_key.split(".")[-1]

                            if routing_key.startswith("processed.telemetry."):
                                payload["type"] = "live_telemetry"

                            await manager.broadcast_to_device(device_id, payload)

        except Exception as e:
            logger.error(f"RabbitMQ consumer error: {e}. Retrying in 5 seconds...")
            await asyncio.sleep(5)


@asynccontextmanager
async def lifespan(app: FastAPI):
    logger.info("Starting API...")

    rabbitmq_task = asyncio.create_task(consume_rabbitmq())

    yield

    logger.info("Shutting down API...")


app = FastAPI(
    title="Solar Tracker API",
    version="1.0.0",
    lifespan=lifespan
)

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
        end_date: datetime = Query(..., description="End timestamp (ISO 8601)")
):
    logger.info(f"Fetching telemetry for {device_id} | Range: {start_date} to {end_date}.")

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
        end_date: datetime = Query(..., description="End timestamp (ISO 8601)")
):
    logger.info(f"Fetching forecast for {device_id} | Range: {start_date} to {end_date}.")

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
            results = cursor.fetchall()

            if results:
                keys_to_remove = [
                    key for key in results[0].keys()
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


# @app.get("/api/v1/current-state/{device_id}")
# def get_current_state(device_id: str):
#     pass


@app.get("/api/v1/assets")
def get_all_assets():
    logger.info("Fetching all assets from pv_assets and wind_assets.")

    client = get_mongodb_client()

    try:
        db = client[MONGODB_DB]

        pv_cursor = db["assets_pv"].find({}, {"_id": 0})
        pv_assets = list(pv_cursor)
        for asset in pv_assets:
            asset["asset_type"] = "pv"

        wind_cursor = db["assets_wind"].find({}, {"_id": 0})
        wind_assets = list(wind_cursor)
        for asset in wind_assets:
            asset["asset_type"] = "wind"

        combined_assets = pv_assets + wind_assets
        combined_assets.sort(key=lambda asset: asset.get("farm_name", "").lower())

        logger.info(f"Query successful. Found {len(pv_assets)} PV and {len(wind_assets)} Wind assets.")
        return combined_assets

    except Exception as e:
        logger.error(f"MongoDB query failed: {str(e)}.")
        raise HTTPException(status_code=500, detail="Failed to fetch assets")

    finally:
        client.close()


@app.websocket("/api/v1/ws/live/{device_id}")
async def websocket_live_stream(websocket: WebSocket, device_id: str):
    await manager.connect(websocket, device_id)
    try:
        while True:
            data = await websocket.receive_text()
    except WebSocketDisconnect:
        manager.disconnect(websocket, device_id)


if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8001, log_level="error")
