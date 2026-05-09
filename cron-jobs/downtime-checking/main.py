import logging
import os
from datetime import datetime, timedelta, timezone

import psycopg2
import requests
from dotenv import load_dotenv
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

EXPO_PUSH_TOKEN = os.environ.get("EXPO_PUSH_TOKEN", "default_token")

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S",
)

logger = logging.getLogger("downtime-checker")


def get_mongo_assets():
    mongo_uri = f"mongodb://{MONGODB_USERNAME}:{MONGODB_PASSWORD}@{MONGODB_HOST}:{MONGODB_PORT}/?authSource=admin"

    try:
        client = MongoClient(mongo_uri, serverSelectionTimeoutMS=5000)
        db = client[MONGODB_DB]
        pv_collection = db["assets_pv"]
        wind_collection = db["assets_wind"]

        assets = list(pv_collection.find({})) + list(wind_collection.find({}))
        return assets
    except Exception as e:
        logger.error(f"MongoDB connection failed: {e}.")
        return []
    finally:
        if "client" in locals():
            client.close()


def send_expo_push_notification(device_id, reason):
    url = "https://exp.host/--/api/v2/push/send"
    payload = {
        "to": EXPO_PUSH_TOKEN,
        "title": "⚠️ SolarTracker Alert",
        "body": f"Asset {device_id} issue detected: {reason}",
        "data": {"device_id": device_id, "alert_type": "downtime"},
    }

    try:
        response = requests.post(url, json=payload, timeout=5)
        response.raise_for_status()
        logger.info(f"Push notification sent successfully for {device_id}.")
    except Exception as e:
        logger.error(f"Failed to send push notification to Expo API: {e}")


def main():
    assets = get_mongo_assets()
    logger.info(f"Starting downtime checking job for {len(assets)} assets.")

    if not assets:
        logger.info("Downtime checking job finished. No assets found.")
        return

    device_ids = [str(asset["device_id"]) for asset in assets]

    now_utc = datetime.now(timezone.utc)
    threshold_time = now_utc - timedelta(minutes=15)

    try:
        conn = psycopg2.connect(
            host=POSTGRES_HOST,
            port=POSTGRES_PORT,
            user=POSTGRES_USERNAME,
            password=POSTGRES_PASSWORD,
            dbname=POSTGRES_NAME,
        )
        cursor = conn.cursor()

        query = """
            SELECT DISTINCT ON (device_id) device_id, time, status 
            FROM telemetry 
            WHERE device_id = ANY(%s) 
            ORDER BY device_id, time DESC
        """

        cursor.execute(query, (device_ids,))
        latest_telemetry = cursor.fetchall()

        telemetry_map = {
            row[0]: {"time": row[1], "status": row[2]} for row in latest_telemetry
        }

        for device_id in device_ids:
            data = telemetry_map.get(device_id)

            if not data:
                logger.warning(f"Device {device_id} has no telemetry records at all.")
                send_expo_push_notification(device_id, "No telemetry data found.")
                continue

            last_time = data["time"]
            current_status = data["status"]

            if last_time < threshold_time:
                logger.warning(
                    f"Device {device_id} is offline. Last seen: {last_time}."
                )
                send_expo_push_notification(device_id, "Offline for over 15 minutes.")
            elif current_status != "OK":
                logger.warning(
                    f"Device {device_id} reported an error. Status: {current_status}."
                )
                send_expo_push_notification(
                    device_id, f"Reported error status: {current_status}."
                )
            else:
                logger.info(f"Device {device_id} is online and healthy.")
                
    except Exception as e:
        logger.error(f"Error during downtime checking: {e}.", exc_info=True)
    finally:
        if "cursor" in locals() and cursor:
            cursor.close()
        if "conn" in locals() and conn:
            conn.close()
        logger.info("Downtime checking job finished.")


if __name__ == "__main__":
    main()
    