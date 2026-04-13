import os
import json
import logging
import pika
import psycopg2
from datetime import datetime

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s [%(levelname)s] [%(name)s] %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S',
    handlers=[logging.StreamHandler(sys.stdout)]
)

logger = logging.getLogger("telemetry_processor")

RABBIT_HOST = os.environ.get("RABBIT_HOST", "localhost")
RABBIT_PORT = int(os.environ.get("RABBIT_PORT", "5672"))
RABBIT_USER = os.environ.get("RABBIT_USER", "admin")
RABBIT_PASS = os.environ.get("RABBIT_PASSWORD", "admin")

DB_HOST = os.environ.get("DB_HOST", "localhost")
DB_PORT = os.environ.get("DB_PORT", "5432")
DB_USER = os.environ.get("DB_USER", "admin")
DB_PASS = os.environ.get("DB_PASSWORD", "admin")
DB_NAME = os.environ.get("DB_NAME", "default_db")

def get_db_connection():
    return psycopg2.connect(
        host=DB_HOST,
        port=DB_PORT,
        user=DB_USER,
        password=DB_PASS,
        dbname=DB_NAME
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
            INSERT INTO telemetry (time, device_id, voltage_v, current_i, irradiance_wm2, temp_c, yaw_angle_deg, status)
            VALUES (%s, %s, %s, %s, %s, %s, %s, %s)
        """
        
        cursor.execute(insert_query, (
            dt_time,
            device_id,
            payload.get("voltage_v"),
            payload.get("current_i"),
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
    credentials = pika.PlainCredentials(RABBIT_USER, RABBIT_PASS)
    parameters = pika.ConnectionParameters(RABBIT_HOST, RABBIT_PORT, '/', credentials)
    
    while True:
        try:
            logger.info("Connecting to RabbitMQ...")
            connection = pika.BlockingConnection(parameters)
            channel = connection.channel()

            queue_name = 'q_telemetry_processor'
            channel.queue_declare(queue=queue_name, durable=True)
            channel.queue_bind(exchange='amq.topic', queue=queue_name, routing_key='telemetry.device.#')
            channel.basic_consume(queue=queue_name, on_message_callback=process_message)

            logger.info(f"Connected to '{queue_name}'. Waiting for messages...")
            
            channel.start_consuming()

        except pika.exceptions.AMQPConnectionError as e:
            logger.warning(f"RabbitMQ connection lost: {e}. Retrying in 5 seconds...")
            time.sleep(5)
            continue

if __name__ == "__main__":
    main()
