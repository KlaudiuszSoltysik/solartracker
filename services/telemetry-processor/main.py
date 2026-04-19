import json
import logging
import os
import sys
import time
import socket
from datetime import datetime

import pika
import psycopg2
from dotenv import load_dotenv

load_dotenv()

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s [%(levelname)s] [%(name)s] %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S',
    handlers=[logging.StreamHandler(sys.stdout)]
)

logging.getLogger("pika").setLevel(logging.WARNING)

logger = logging.getLogger("telemetry_processor")

RABBITMQ_HOST = os.environ.get("RABBITMQ_HOST", "localhost")
RABBITMQ_PORT = int(os.environ.get("RABBITMQ_PORT", "5672"))
RABBITMQ_USERNAME = os.environ.get("RABBITMQ_USERNAME", "admin")
RABBITMQ_PASSWORD = os.environ.get("RABBITMQ_PASSWORD", "admin")

POSTGRES_HOST = os.environ.get("POSTGRES_HOST", "localhost")
POSTGRES_PORT = os.environ.get("POSTGRES_PORT", "5432")
POSTGRES_USERNAME = os.environ.get("POSTGRES_USERNAME", "admin")
POSTGRES_PASSWORD = os.environ.get("POSTGRES_PASSWORD", "admin")
POSTGRES_DB = os.environ.get("POSTGRES_DB", "default_db")


def get_db_connection():
    return psycopg2.connect(
        host=POSTGRES_HOST,
        port=POSTGRES_PORT,
        user=POSTGRES_USERNAME,
        password=POSTGRES_PASSWORD,
        dbname=POSTGRES_DB
    )


def process_message(ch, method, properties, body):
    try:
        payload = json.loads(body.decode())

        routing_key = method.routing_key
        device_id = routing_key.split('.')[-1]

        logger.info(f"Received telemetry | Device: {device_id}")

        conn = get_db_connection()
        cursor = conn.cursor()

        dt_time = datetime.fromtimestamp(payload["timestamp"])

        insert_query = """
                       INSERT INTO telemetry (time, device_id, voltage_v, current_a, irradiance_wm2, temp_c,
                                              yaw_angle_deg, status)
                       VALUES (%s, %s, %s, %s, %s, %s, %s, %s) \
                       """

        cursor.execute(insert_query, (
            dt_time,
            device_id,
            payload.get("voltage_v"),
            payload.get("current_a"),
            payload.get("irradiance_wm2"),
            payload.get("temp_c"),
            payload.get("yaw_angle_deg"),
            payload.get("status")
        ))

        conn.commit()
        cursor.close()
        conn.close()

        logger.info(f"Telemetry saved | Device: {device_id}")

        ch.basic_ack(delivery_tag=method.delivery_tag)

    except psycopg2.OperationalError as e:
        logger.error(f"Database connection failed: {e}. Requeueing message...")
        time.sleep(5)
        ch.basic_nack(delivery_tag=method.delivery_tag, requeue=True)

    except Exception as e:
        logger.error(f"Error parsing telemetry: {e}", exc_info=True)
        ch.basic_nack(delivery_tag=method.delivery_tag, requeue=False)


def main():
    credentials = pika.PlainCredentials(RABBITMQ_USERNAME, RABBITMQ_PASSWORD)
    parameters = pika.ConnectionParameters(RABBITMQ_HOST, RABBITMQ_PORT, '/', credentials)

    while True:
        try:
            logger.info("Connecting to RABBITMQMQ...")
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
            time.sleep(5)


if __name__ == "__main__":
    main()
