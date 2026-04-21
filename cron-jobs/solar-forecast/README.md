# Solar Forecasting Module

This Python script is designed to automate the process of forecasting solar power generation based on weather data and PV asset information.

## Files Content

- **`main.py`:**
  - Import necessary libraries.
  - Define constants for PostgreSQL connection details, MongoDB credentials, and MongoDB database name.
  - Load environment variables from `.env`.
  - Connect to PostgreSQL using `psycopg2`, execute SQL queries, and handle exceptions.
  - Fetch weather data from OpenMeteo API and calculate power generation based on irradiance, temperature, and maximum power output.

- **`utils.py`:**
  - Define constants for MongoDB connection details, including host, port, username, password, and database name.
  - Connect to MongoDB using `MongoClient`, execute SQL queries, and handle exceptions.

## Usage

1. Ensure you have the following environment variables set:
   - `POSTGRES_HOST`: The hostname or IP address of your PostgreSQL server.
   - `POSTGRES_PORT`: The port number for your PostgreSQL server (default is 5432).
   - `POSTGRES_USERNAME`: Your PostgreSQL username.
   - `POSTGRES_PASSWORD`: Your PostgreSQL password.
   - `POSTGRES_NAME`: The name of the PostgreSQL database.

2. Run the script using:
   ```bash
   python main.py
   ```

## Technical Architecture

- **Database:**
  - MongoDB: Stores weather data and PV asset information.
  - PostgreSQL: Handles SQL queries, data retrieval, and transaction management.

- **Python Code:**
  - Uses `psycopg2` for PostgreSQL database interactions.
  - Utilizes `pvlib` for solar radiation calculations.
  - Fetches weather data from OpenMeteo API using `requests`.
  - Calculates power generation based on irradiance, temperature, and maximum power output.

- **Logging:**
  - Logs messages to the console with a specified level (INFO in this case).

## Purpose

This module is designed for automated forecasting of solar power generation. It leverages PostgreSQL for database management, MongoDB for storing data, and Python's `psycopg2` library for interacting with the database.

## Dependencies

- **Python:** Ensure you have Python installed.
- **PostgreSQL:** Install PostgreSQL on your system if it's not already available.
- **pvlib:** A Python library for solar radiation calculations.

## Example Usage

1. Set up environment variables:
   ```bash
   export POSTGRES_HOST=localhost
   export POSTGRES_PORT=5432
   export POSTGRES_USERNAME=admin
   export POSTGRES_PASSWORD=admin
   export POSTGRES_NAME=default_db
   ```

2. Run the script:
   ```bash
   python main.py
   ```

This will fetch weather data, calculate power generation based on irradiance, temperature, and maximum power output for PV assets, and insert the forecasts into MongoDB.

## Next Steps

- **Documentation:** Add detailed documentation for this module.
- **Testing:** Write unit tests to ensure the script functions as expected.
- **Maintenance:** Regularly update the codebase with new features or bug fixes.

Feel free to ask if you have any questions or need further assistance!