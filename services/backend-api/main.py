import logging
import os
from contextlib import asynccontextmanager
from datetime import datetime

import psycopg2
from dotenv import load_dotenv
from fastapi import FastAPI, HTTPException, Query
from fastapi.middleware.cors import CORSMiddleware
from psycopg2.extras import RealDictCursor

load_dotenv()

POSTGRES_HOST = os.environ.get("POSTGRES_HOST", "localhost")
POSTGRES_PORT = os.environ.get("POSTGRES_PORT", "5432")
POSTGRES_USERNAME = os.environ.get("POSTGRES_USERNAME", "admin")
POSTGRES_PASSWORD = os.environ.get("POSTGRES_PASSWORD", "admin")
POSTGRES_NAME = os.environ.get("POSTGRES_NAME", "default_db")

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S"
)

logger = logging.getLogger("backend-api")

logging.getLogger("uvicorn.access").setLevel(logging.WARNING)


def get_db_connection():
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


@asynccontextmanager
async def lifespan(app: FastAPI):
    logger.info("Starting API...")

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

    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            query = """
                    SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                    FROM telemetry
                    WHERE device_id = %s
                      AND time >= %s
                      AND time <= %s
                    ORDER BY time DESC; \
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

    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            query = """
                    SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                    FROM forecast
                    WHERE device_id = %s
                      AND time >= %s
                      AND time <= %s
                    ORDER BY time DESC; \
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


if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
