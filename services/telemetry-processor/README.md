# Telemetry Processor Module

## Overview

This module provides a high-level API to process telemetry data from various sources using RabbitMQ for message delivery.

## Dependencies

- RabbitMQ: For message delivery and processing
- psycopg2: For database operations (optional)

## Installation

1. Install the required dependencies:
   ```bash
   pip install pika psycopg2-binary
   ```

2. Clone or download the project directory:

```bash
git clone https://github.com/yourusername/telemetry-processor.git
cd telemetry-processor
```

3. Modify the `main.py` file to include RabbitMQ credentials and database connection details.

## Usage

1. Start the Telemetry Processor:
   ```bash
   python main.py
   ```

2. Connect to RabbitMQ for message delivery:
   ```python
   import pika

   credentials = pika.PlainCredentials(RABBITMQ_USERNAME, RABBITMQ_PASSWORD)
   parameters = pika.ConnectionParameters(RABBITMQ_HOST, RABBITMQ_PORT, '/', credentials)

   while True:
       try:
           connection = pika.BlockingConnection(parameters)
           channel = connection.channel()
           queue_name = 'q_telemetry_processor'
           channel.queue_declare(queue=queue_name, durable=True)
           channel.queue_bind(exchange='amq.topic', queue=queue_name, routing_key='telemetry.device.#')
           channel.basic_consume(queue=queue_name, on_message_callback=process_message)

           logger.info(f"Connected to '{queue_name}'. Waiting for messages...")

           channel.start_consuming()
       except Exception as e:
           logger.warning(f"RABBITMQ connection lost: {e}. Retrying in 5 seconds...")
   ```

## Configuration

- **RABBITMQ_HOST**: The RabbitMQ host address.
- **RABBITMQ_PORT**: The RabbitMQ port number (default is 5672).
- **RABBITMQ_USERNAME**: The RabbitMQ username.
- **RABBITMQ_PASSWORD**: The RabbitMQ password.
- **POSTGRES_HOST**: The PostgreSQL host address.
- **POSTGRES_PORT**: The PostgreSQL port number (default is 5432).
- **POSTGRES_USERNAME**: The PostgreSQL username.
- **POSTGRES_PASSWORD**: The PostgreSQL password.
- **POSTGRES_DB**: The PostgreSQL database name.

## Logging

The logging configuration is set up in the `logging.ini` file located at:
```
../../services/telemetry-processor/logging.ini
```

You can customize the log level and format as needed.

## Error Handling

Error handling is implemented using try-except blocks. If an error occurs during message processing, it will be caught and logged.

## Conclusion

This module provides a simple API for Telemetry Processor to process telemetry data from various sources using RabbitMQ for message delivery. The configuration file should be updated with your specific credentials and database details.