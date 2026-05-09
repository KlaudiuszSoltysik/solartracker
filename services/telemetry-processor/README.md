# Telemetry Processor

This module processes telemetry data from various devices and stores it in a PostgreSQL database for analysis.

## Files Content

- **services/telemetry-processor/main.py**
  - This file contains the main function that handles incoming messages from RabbitMQ.
  - It connects to the RabbitMQ server, binds the message queue with the "amq.topic" exchange, and sets up a basic connection.
  - The `process_message` function processes each telemetry message received. It extracts relevant data such as device ID, voltage, current, irradiance, temperature, yaw angle, status, and saves it to the PostgreSQL database.
  - If an error occurs during processing, it retries after a delay of 5 seconds.

## Technical Architecture

- **RabbitMQ**: The RabbitMQ server is used for message exchange between the Telemetry Processor and other applications. It handles routing, binding, and exchanging messages with the specified exchange name.
  
- **PostgreSQL**: The PostgreSQL database is used to store telemetry data. It has a dedicated table named `telemetry` where each row represents a single telemetry entry.

## Purpose

The purpose of this module is to process and analyze telemetry data from various devices, enabling real-time monitoring and analysis of environmental parameters such as temperature, irradiance, voltage, current, and more.

## Setup

- **Environment Variables**: Ensure that the RabbitMQ host, port, username, password, PostgreSQL database credentials are set in your environment variables.
  - Example: `RABBITMQ_HOST=localhost`
  - Example: `POSTGRES_HOST=postgres`
  - Example: `POSTGRES_USERNAME=admin`
  - Example: `POSTGRES_PASSWORD=admin`

- **PostgreSQL Database**: Ensure that the PostgreSQL server is running and accessible.

## Usage

1. Install the required libraries:
   ```bash
   pip install pika psycopg2-binary
   ```

2. Run the Telemetry Processor module:
   ```bash
   python services/telemetry-processor/main.py
   ```

3. Connect to RabbitMQ server using `rabbitmqctl` (if not already installed):
   ```bash
   rabbitmqctl stop
   rabbitmqctl start
   rabbitmqctl set_permissions -p / admin:password
   rabbitmqctl add_user your_username your_password
   rabbitmqctl set_permissions -p / your_username ".*"
   ```

4. Connect to the PostgreSQL database:
   ```bash
   psql -U postgres -d default_db
   ```

5. Replace `your_username` and `your_password` with your actual credentials.

6. Run the Telemetry Processor module again after setting up the environment variables.

## Next Steps

- **Data Storage**: Store telemetry data in a PostgreSQL database for future analysis.
  - Example: Create a table named `telemetry` with columns for device ID, timestamp, voltage, current, irradiance, temperature, yaw angle, status, and more.
  
- **Error Handling**: Improve error handling to make the module more robust.

- **Documentation**: Add detailed documentation for the Telemetry Processor module.

## Contributing

Feel free to contribute to this project by opening pull requests or submitting feature requests. Let's work together to improve the Telemetry Processor!

---

This README.md is a basic template and can be expanded with additional details, examples, and specific requirements.