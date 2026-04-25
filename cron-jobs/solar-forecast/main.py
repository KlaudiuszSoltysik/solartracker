import json
import logging
import os
from datetime import datetime, timezone, timedelta

import pika
import psycopg2
import pvlib
import requests
from dotenv import load_dotenv
from psycopg2.extras import execute_values
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

logger = logging.getLogger("solar-forecast")


def get_mongo_assets():
    mongo_uri = f"mongodb://{MONGODB_USERNAME}:{MONGODB_PASSWORD}@{MONGODB_HOST}:{MONGODB_PORT}/?authSource=admin"

    try:
        client = MongoClient(mongo_uri, serverSelectionTimeoutMS=5000)
        db = client[MONGODB_DB]
        collection = db["assets_pv"]

        assets = list(collection.find({}))
        return assets
    except Exception as e:
        logger.error(f"MongoDB connection failed: {e}.")
        return []
    finally:
        if "client" in locals():
            client.close()


def fetch_weather_forecast(lat, lon):
    url = f"https://api.open-meteo.com/v1/forecast?latitude={lat}&longitude={lon}&minutely_15=temperature_2m,shortwave_radiation&timezone=UTC&forecast_days=3"
    response = requests.get(url)
    response.raise_for_status()
    return response.json()


def calculate_power(irradiance_wm2, temp_c, max_power_w, gamma_pdc, temp_ref):
    if irradiance_wm2 <= 0:
        return 0.0

    forecasted_dc_power = pvlib.pvsystem.pvwatts_dc(
        irradiance_wm2,
        temp_c,
        max_power_w,
        gamma_pdc,
        temp_ref
    )

    return max(0.0, round(float(forecasted_dc_power), 2))


def main():
    pv_assets = get_mongo_assets()

    logger.info(f"Starting solar power forecasting job for {len(pv_assets)} assets.")

    if not pv_assets:
        logger.info("Forecasting job finished. No assets found.")
        return

    forecasts_to_insert = []
    updated_device_ids = set()

    for farm in pv_assets:
        try:
            device_id = farm["device_id"]
            max_power_w = farm["max_power_w"]
            lat = farm["lat"]
            lon = farm["lon"]
            gamma_pdc = farm["gamma_pdc"]
            temp_ref = farm["temp_ref"]

            logger.info(f"Processing farm: {farm['farm_name']}.")

            weather_data = fetch_weather_forecast(lat, lon)
            minutely = weather_data["minutely_15"]

            current_time = datetime.now(timezone.utc)

            for i in range(len(minutely["time"])):
                dt_time = datetime.fromisoformat(minutely["time"][i])

                if dt_time.tzinfo is None:
                    dt_time = dt_time.replace(tzinfo=timezone.utc)

                dt_time = dt_time - timedelta(minutes=15)

                if dt_time < current_time:
                    continue

                irradiance = minutely["shortwave_radiation"][i]
                temp = minutely["temperature_2m"][i]

                if irradiance is None or temp is None:
                    continue

                forecasted_power = calculate_power(irradiance, temp, max_power_w, gamma_pdc, temp_ref)

                forecasts_to_insert.append((dt_time, device_id, forecasted_power, irradiance, temp, current_time))
                updated_device_ids.add(device_id)

        except Exception as e:
            logger.error(f"Error during processing farm: {farm['farm_name']}.", exc_info=True)

    if not forecasts_to_insert:
        logger.warning("No forecasts generated. Exiting.")
        return

    try:
        conn = psycopg2.connect(host=POSTGRES_HOST, port=POSTGRES_PORT, user=POSTGRES_USERNAME,
                                password=POSTGRES_PASSWORD, dbname=POSTGRES_NAME)
        cursor = conn.cursor()

        query = """
                INSERT INTO forecast (time, device_id, power_w, irradiance_wm2, temp_c, forecasted_at)
                VALUES %s ON CONFLICT (time, device_id) 
                DO
                UPDATE SET
                    power_w = EXCLUDED.power_w,
                    irradiance_wm2 = EXCLUDED.irradiance_wm2,
                    temp_c = EXCLUDED.temp_c,
                    forecasted_at = EXCLUDED.forecasted_at;
                """

        execute_values(cursor, query, forecasts_to_insert)
        conn.commit()
        logger.info(f"Successfully updated {len(forecasts_to_insert)} forecast intervals in DB.")

        try:
            credentials = pika.PlainCredentials(RABBITMQ_USERNAME, RABBITMQ_PASSWORD)
            parameters = pika.ConnectionParameters(RABBITMQ_HOST, RABBITMQ_PORT, "/", credentials)
            rabbit_conn = pika.BlockingConnection(parameters)
            channel = rabbit_conn.channel()

            channel.exchange_declare(exchange="processed_telemetry", exchange_type="topic", durable=True)

            for dev_id in updated_device_ids:
                ping_payload = {
                    "type": "forecast_update",
                    "device_id": dev_id,
                    "timestamp": datetime.now(timezone.utc).isoformat()
                }

                routing_key = f"processed.forecast.{dev_id}"

                channel.basic_publish(
                    exchange="processed_telemetry",
                    routing_key=routing_key,
                    body=json.dumps(ping_payload),
                    properties=pika.BasicProperties(delivery_mode=1, expiration="180000")
                )

            rabbit_conn.close()
            logger.info("Sent update pings to RabbitMQ successfully.")
        except Exception as mq_err:
            logger.error(f"Failed to send ping to RabbitMQ: {mq_err}")

    except Exception as e:
        logger.error(f"Error during forecasting DB save: {e}.", exc_info=True)
    finally:
        if "cursor" in locals() and cursor: cursor.close()
        if "conn" in locals() and conn: conn.close()
        logger.info("Forecasting job finished.")


if __name__ == "__main__":
    main()
