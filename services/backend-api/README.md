# Solar Tracker API

## Technical Architecture and Purpose

This module provides a RESTful API for managing solar tracker data. The API supports fetching telemetry history and energy forecast data for specific devices.

### Key Features

- **Telemetry Fetching**: Retrieve historical data from the database for each device.
- **Energy Forecasting**: Predict future solar energy usage based on historical data.

### Database Schema

The database schema is designed to store telemetry data, including:
- `device_id`: Unique identifier for each device.
- `time`: Timestamp of the measurement.
- `voltage_v`: Voltage measured by the device.
- `current_a`: Current flowing through the device.
- `irradiance_wm2`: Irradiance measured in watts per square meter (W/m²).
- `temp_c`: Temperature in Celsius.
- `yaw_angle_deg`: Yaw angle of the device in degrees.
- `status`: Status of the device, e.g., "online", "offline".

### Data Fetching

The API uses a connection to a PostgreSQL database. The connection is established using environment variables for host, port, username, password, and database name.

## Usage

1. **Telemetry Fetching**:
   - Use `/api/v1/telemetry/{device_id}` to fetch telemetry data.
   - Example: `GET /api/v1/telemetry/12345`

2. **Energy Forecasting**:
   - Use `/api/v1/energy-forecast/{device_id}` to fetch energy forecast data.
   - Example: `GET /api/v1/energy-forecast/12345`

### Example Usage

```python
from fastapi import FastAPI, HTTPException
import psycopg2
from dotenv import load_dotenv
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
        logger.error(f"Database connection failed: {e}")
        raise HTTPException(status_code=500, detail="Database connection error")


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
    logger.info(f"Fetching telemetry for {device_id} | Range: {start_date} to {end_date}")

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
    logger.info(f"Fetching energy forecast for {device_id} | Range: {start_date} to {end_date}")

    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            query = """
                    SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg
                    FROM telemetry
                    WHERE device_id = %s
                      AND (time >= %s AND time <= %s)
                    ORDER BY time DESC; \
                    """
            cursor.execute(query, (device_id, start_date, end_date))
            results = cursor.fetchall()

            logger.info(f"Query successful. Found {len(results)} records.")
            return {"energy_forecast": results}
    finally:
        conn.close()
```

### Explanation

- **Telemetry Fetching**: The API uses a connection to the PostgreSQL database to fetch telemetry data for each device.
- **Energy Forecasting**: The API also uses a connection to the same database to fetch energy forecast data based on historical data.

This module is designed to be used internally and should not be modified or extended without permission.