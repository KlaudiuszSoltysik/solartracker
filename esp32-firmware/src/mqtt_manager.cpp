#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include "config.h"
#include "motor_controller.h"
#include "mqtt_manager.h"
#include "time_manager.h"
#include "yaw_controller.h"

namespace
{
    WiFiClient wifiClient;
    PubSubClient mqttClient(wifiClient);
    unsigned long lastReconnectAttempt = 0;

    String telemetryTopic()
    {
        return String(MQTT_TELEMETRY_TOPIC_PREFIX) + DEVICE_ID;
    }

    String commandTopic()
    {
        return String(MQTT_COMMAND_TOPIC_PREFIX) + DEVICE_ID;
    }

    float estimateIrradianceWm2(const SensorData &data)
    {
        float averageLux = ((float)data.luxLeft + (float)data.luxRight) / 2.0f;
        return averageLux / LUX_TO_IRRADIANCE_DIVISOR;
    }

    void handleCommandPayload(byte *payload, unsigned int length)
    {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, payload, length);

        if (error)
        {
            Serial.printf("[MQTT] Command JSON parse error: %s\n", error.c_str());
            return;
        }

        if (doc["target_yaw"].is<float>() || doc["target_yaw"].is<int>())
        {
            float targetYaw = doc["target_yaw"].as<float>();
            targetYaw = constrain(targetYaw, DEFAULT_MIN_YAW_ANGLE, DEFAULT_MAX_YAW_ANGLE);

            setTrackingMode(MODE_MANUAL);
            setManualTargetAngle(targetYaw);

            Serial.printf("[MQTT] Manual target yaw received: %.2f deg\n", targetYaw);
        }
    }

    void onMqttMessage(char *topic, byte *payload, unsigned int length)
    {
        Serial.printf("[MQTT] Message received on %s\n", topic);
        handleCommandPayload(payload, length);
    }

    bool reconnectMqtt()
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("[MQTT] Wi-Fi disconnected. Reconnecting Wi-Fi...");
            WiFi.reconnect();
            return false;
        }

        Serial.printf("[MQTT] Connecting to %s:%d as %s...\n", MQTT_BROKER, MQTT_PORT, DEVICE_ID);

        bool connected = strlen(MQTT_USER) > 0
                             ? mqttClient.connect(DEVICE_ID, MQTT_USER, MQTT_PASS)
                             : mqttClient.connect(DEVICE_ID);
        if (!connected)
        {
            Serial.printf("[MQTT] Connection failed, state: %d\n", mqttClient.state());
            return false;
        }

        String topic = commandTopic();
        mqttClient.subscribe(topic.c_str());

        Serial.printf("[MQTT] Connected. Listening on %s\n", topic.c_str());
        return true;
    }
}

void initMqtt()
{
    mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
    mqttClient.setCallback(onMqttMessage);
    mqttClient.setBufferSize(512);
}

void handleMqtt()
{
    if (mqttClient.connected())
    {
        mqttClient.loop();
        return;
    }

    unsigned long now = millis();
    if (now - lastReconnectAttempt >= MQTT_RECONNECT_INTERVAL)
    {
        lastReconnectAttempt = now;
        reconnectMqtt();
    }
}

bool publishTelemetry(const SensorData &data)
{
    if (!mqttClient.connected())
    {
        Serial.println("[MQTT] Telemetry skipped: MQTT is not connected.");
        return false;
    }

    unsigned long timestamp = getUnixTime();
    if (timestamp < 10000)
    {
        Serial.println("[MQTT] Telemetry skipped: system time is not synchronized.");
        return false;
    }

    JsonDocument doc;
    doc["timestamp"] = timestamp;
    doc["voltage_v"] = data.voltage;
    doc["current_a"] = data.current / 1000.0f;
    doc["irradiance_wm2"] = estimateIrradianceWm2(data);
    doc["temp_c"] = data.temperature;
    doc["yaw_angle_deg"] = getCurrentYawAngle();
    doc["status"] = getMotorStatus();

    char payload[256];
    size_t payloadLength = serializeJson(doc, payload, sizeof(payload));
    if (payloadLength == 0 || payloadLength >= sizeof(payload))
    {
        Serial.println("[MQTT] Telemetry serialization failed or payload is too large.");
        return false;
    }

    String topic = telemetryTopic();
    bool published = mqttClient.publish(topic.c_str(), (const uint8_t *)payload, payloadLength);

    if (published)
    {
        Serial.printf("[MQTT] Telemetry sent to %s: %s\n", topic.c_str(), payload);
    }
    else
    {
        Serial.println("[MQTT] Telemetry publish failed.");
    }

    return published;
}

bool isMqttConnected()
{
    return mqttClient.connected();
}
