# Services Backend-API

## Overview

This is a Python-based FastAPI application designed to provide an API for managing solar tracker data and energy forecasts.

## Technical Architecture

The backend API uses the following components:

- **Database**: A PostgreSQL database with a single table `telemetry` that stores historical solar tracker data.
  - The `device_id` column uniquely identifies each device.
  - The `time`, `voltage_v`, `current_a`, `irradiance_wm2`, `temp_c`, `yaw_angle_deg`, and `status` columns store the relevant telemetry data.

- **FastAPI**: A Python library for building web applications that uses FastAPI as its framework. It provides a simple API to interact with the database.
  - The application is built using FastAPI, which simplifies the process of creating APIs by providing tools like middleware and decorators.

## Purpose

The purpose of this module is to provide an easy-to-use API for managing solar tracker data and energy forecasts. Users can fetch historical telemetry data and forecast future energy consumption based on device-specific parameters.

## Installation

To use this module, you need to have the following installed:

- Python 3.x
- psycopg2 (PostgreSQL database adapter)
- FastAPI (Python library for building web applications)

You can install these dependencies using pip:

```bash
pip install fastapi psycopg2
```

## Usage

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

### Example Code

Here's an example of how you might structure your FastAPI application:

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect
import os

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect
import os

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect
import os

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)
```

### Running the Application

1. **Database Setup**: Ensure that you have a PostgreSQL database set up with the `telemetry` table and appropriate schema.
2. **FastAPI Application**: Create a FastAPI application to handle API requests.

```python
from fastapi import FastAPI, HTTPException
from sqlalchemy.orm import sessionmaker
from psycopg2 import connect

app = FastAPI()

# Database setup
os.environ["POSTGRES_HOST"] = "localhost"
os.environ["POSTGRES_PORT"] = "5432"
os.environ["POSTGRES_USERNAME"] = "admin"
os.environ["POSTGRES_PASSWORD"] = "admin"
os.environ["POSTGRES_NAME"] = "default_db"

DATABASE_URL = os.getenv("POSTGRES_URL", "postgresql://admin:admin@localhost:5432/default_db")
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=DATABASE_URL)

@app.get("/api/v1/telemetry/{device_id}")
def get_telemetry_history(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, voltage_v, current_a, irradiance_wm2, temp_c, yaw_angle_deg, status
                FROM telemetry
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

@app.get("/api/v1/energy-forecast/{device_id}")
def get_energy_forecast(device_id: str):
    conn = SessionLocal()
    try:
        with conn.cursor() as cursor:
            query = """
                SELECT time, power_w, irradiance_wm2, temp_c, wind_speed_mps, forecasted_at
                FROM forecast
                WHERE device_id = %s
                  AND time >= %s
                  AND time <= %s
              ORDER BY time DESC;
            """
            cursor.execute(query, (device_id, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            results = cursor.fetchall()
    finally:
        conn.close()

if __name__ == "__main__":
    import