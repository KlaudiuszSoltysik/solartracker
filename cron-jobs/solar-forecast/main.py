import logging
import os
from datetime import datetime, timezone, timedelta

import psycopg2
import pvlib
import requests
from psycopg2.extras import execute_values
from pymongo import MongoClient

logging.basicConfig(level=logging.INFO, format="%(asctime)s [%(levelname)s] %(message)s")
logger = logging.getLogger("solar-forecast")

DB_HOST = os.environ.get("DB_HOST", "localhost")
DB_USER = os.environ.get("DB_USER", "admin")
DB_PASSWORD = os.environ.get("DB_PASSWORD", "admin")
DB_NAME = os.environ.get("DB_NAME", "default_db")

MONGO_HOST = os.environ.get("MONGO_HOST", "localhost")
MONGO_PORT = os.environ.get("MONGO_PORT", "27017")
MONGO_USER = os.environ.get("MONGO_USER", "admin")
MONGO_PASSWORD = os.environ.get("MONGO_PASSWORD", "admin")
MONGO_DB = os.environ.get("MONGO_DB", "default_db")


def get_mongo_assets():
    mongo_uri = f"mongodb://{MONGO_USER}:{MONGO_PASSWORD}@{MONGO_HOST}:{MONGO_PORT}/?authSource=admin"

    try:
        client = MongoClient(mongo_uri, serverSelectionTimeoutMS=5000)
        db = client[MONGO_DB]
        collection = db['assets_pv']

        assets = list(collection.find({}))
        return assets
    except Exception as e:
        logger.error(f"MongoDB connection failed: {e}")
        return []
    finally:
        if 'client' in locals():
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

    logger.info(f"Starting solar power forecasting job started for {len(pv_assets)} assets.")

    if not pv_assets:
        logger.info("Forecasting job finished.")
        return

    forecasts_to_insert = []

    for farm in pv_assets:
        try:
            device_id = farm["device_id"]
            max_power = farm["max_power_w"]
            lat = farm["lat"]
            lon = farm["lon"]
            gamma = farm["gamma_pdc"]
            ref = farm["temp_ref"]

            logger.info(f"Processing farm: {farm['farm_name']}")

            weather_data = fetch_weather_forecast(lat, lon)
            minutely = weather_data['minutely_15']

            current_time = datetime.now(timezone.utc)

            for i in range(len(minutely['time'])):
                dt_time = datetime.fromisoformat(minutely['time'][i])

                if dt_time.tzinfo is None:
                    dt_time = dt_time.replace(tzinfo=timezone.utc)

                dt_time = dt_time - timedelta(minutes=15)

                if dt_time < current_time:
                    continue

                irradiance = minutely['shortwave_radiation'][i]
                temp = minutely['temperature_2m'][i]

                if irradiance is None or temp is None:
                    continue

                forecasted_power = calculate_power(irradiance, temp, max_power, gamma, ref)

                forecasts_to_insert.append(
                    (dt_time, device_id, forecasted_power, irradiance, temp, current_time))
        except Exception as e:
            logger.error(f"Error during processing processing farm: {farm['farm_name']}", exc_info=True)

    if not forecasts_to_insert:
        logger.warning("No forecasts generated. Exiting.")
        return

    try:
        conn = psycopg2.connect(host=DB_HOST, user=DB_USER, password=DB_PASSWORD, dbname=DB_NAME)
        cursor = conn.cursor()

        query = """
                INSERT INTO forecast (time, device_id, power_w, irradiance_wm2, temp_c, forecasted_at)
                VALUES %s ON CONFLICT (time, device_id) 
            DO
                UPDATE SET
                    power_w = EXCLUDED.power_w,
                    irradiance_wm2 = EXCLUDED.irradiance_wm2,
                    temp_c = EXCLUDED.temp_c,
                    forecasted_at = EXCLUDED.forecasted_at; \
                """

        execute_values(cursor, query, forecasts_to_insert)
        conn.commit()

        logger.info(f"Successfully updated {len(forecasts_to_insert)} forecast intervals across all farms.")

    except Exception as e:
        logger.error(f"Error during forecasting: {e}", exc_info=True)
    finally:
        if 'cursor' in locals() and cursor: cursor.close()
        if 'conn' in locals() and conn: conn.close()
        logger.info("Forecasting job finished.")


if __name__ == "__main__":
    main()
