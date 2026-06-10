#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include "esp_event.h"
#include "esp_idf_version.h"
#include "mqtt_client.h"
#include "config.h"
#include "motor_controller.h"
#include "mqtt_manager.h"
#include "secrets.h"
#include "time_manager.h"
#include "yaw_controller.h"

namespace
{
    esp_mqtt_client_handle_t mqttClient = nullptr;
    volatile bool mqttConnected = false;
    unsigned long lastWifiReconnectAttempt = 0;

    const char MQTT_ROOT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIICjjCCAjOgAwIBAgIQf/NXaJvCTjAtkOGKQb0OHzAKBggqhkjOPQQDAjBQMSQw
IgYDVQQLExtHbG9iYWxTaWduIEVDQyBSb290IENBIC0gUjQxEzARBgNVBAoTCkds
b2JhbFNpZ24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMjMxMjEzMDkwMDAwWhcN
MjkwMjIwMTQwMDAwWjA7MQswCQYDVQQGEwJVUzEeMBwGA1UEChMVR29vZ2xlIFRy
dXN0IFNlcnZpY2VzMQwwCgYDVQQDEwNXRTEwWTATBgcqhkjOPQIBBggqhkjOPQMB
BwNCAARvzTr+Z1dHTCEDhUDCR127WEcPQMFcF4XGGTfn1XzthkubgdnXGhOlCgP4
mMTG6J7/EFmPLCaY9eYmJbsPAvpWo4IBAjCB/zAOBgNVHQ8BAf8EBAMCAYYwHQYD
VR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMBIGA1UdEwEB/wQIMAYBAf8CAQAw
HQYDVR0OBBYEFJB3kjVnxP+ozKnme9mAeXvMk/k4MB8GA1UdIwQYMBaAFFSwe61F
uOJAf/sKbvu+M8k8o4TVMDYGCCsGAQUFBwEBBCowKDAmBggrBgEFBQcwAoYaaHR0
cDovL2kucGtpLmdvb2cvZ3NyNC5jcnQwLQYDVR0fBCYwJDAioCCgHoYcaHR0cDov
L2MucGtpLmdvb2cvci9nc3I0LmNybDATBgNVHSAEDDAKMAgGBmeBDAECATAKBggq
hkjOPQQDAgNJADBGAiEAokJL0LgR6SOLR02WWxccAq3ndXp4EMRveXMUVUxMWSMC
IQDspFWa3fj7nLgouSdkcPy1SdOR2AGm9OQWs7veyXsBwA==
-----END CERTIFICATE-----
-----BEGIN CERTIFICATE-----
MIIB3DCCAYOgAwIBAgINAgPlfvU/k/2lCSGypjAKBggqhkjOPQQDAjBQMSQwIgYD
VQQLExtHbG9iYWxTaWduIEVDQyBSb290IENBIC0gUjQxEzARBgNVBAoTCkdsb2Jh
bFNpZ24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMTIxMTEzMDAwMDAwWhcNMzgw
MTE5MDMxNDA3WjBQMSQwIgYDVQQLExtHbG9iYWxTaWduIEVDQyBSb290IENBIC0g
UjQxEzARBgNVBAoTCkdsb2JhbFNpZ24xEzARBgNVBAMTCkdsb2JhbFNpZ24wWTAT
BgcqhkjOPQIBBggqhkjOPQMBBwNCAAS4xnnTj2wlDp8uORkcA6SumuU5BwkWymOx
uYb4ilfBV85C+nOh92VC/x7BALJucw7/xyHlGKSq2XE/qNS5zowdo0IwQDAOBgNV
HQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUVLB7rUW44kB/
+wpu+74zyTyjhNUwCgYIKoZIzj0EAwIDRwAwRAIgIk90crlgr/HmnKAWBVBfw147
bmF0774BxL4YSFlhgjICICadVGNA3jdgUM/I2O2dgq43mLyjj0xMqTQrbO/7lZsm
-----END CERTIFICATE-----
)EOF";

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

    void handleCommandPayload(const char *payload, int length)
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

    void subscribeToCommandTopic()
    {
        String topic = commandTopic();
        int messageId = esp_mqtt_client_subscribe(mqttClient, topic.c_str(), 1);
        Serial.printf("[MQTT] Subscribing to %s, msg_id=%d\n", topic.c_str(), messageId);
    }

    void onMqttEvent(void *handlerArgs, esp_event_base_t base, int32_t eventId, void *eventData)
    {
        (void)handlerArgs;
        (void)base;

        esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)eventData;

        switch ((esp_mqtt_event_id_t)eventId)
        {
        case MQTT_EVENT_CONNECTED:
            mqttConnected = true;
            Serial.println("[MQTT] Connected via WSS.");
            subscribeToCommandTopic();
            break;

        case MQTT_EVENT_DISCONNECTED:
            mqttConnected = false;
            Serial.println("[MQTT] Disconnected.");
            break;

        case MQTT_EVENT_DATA:
            Serial.printf("[MQTT] Message received on %.*s\n", event->topic_len, event->topic);
            handleCommandPayload(event->data, event->data_len);
            break;

        case MQTT_EVENT_PUBLISHED:
            Serial.printf("[MQTT] Telemetry publish acknowledged, msg_id=%d\n", event->msg_id);
            break;

        case MQTT_EVENT_ERROR:
            mqttConnected = false;
            Serial.println("[MQTT] Connection error.");
            break;

        default:
            break;
        }
    }
}

void initMqtt()
{
    esp_mqtt_client_config_t mqttConfig = {};

#if ESP_IDF_VERSION_MAJOR >= 5
    mqttConfig.broker.address.uri = MQTT_BROKER_URI;
    mqttConfig.broker.verification.certificate = MQTT_ROOT_CA;
    mqttConfig.credentials.client_id = DEVICE_ID;
    mqttConfig.credentials.username = MQTT_USERNAME;
    mqttConfig.credentials.authentication.password = MQTT_PASSWORD;
    mqttConfig.session.keepalive = 60;
    mqttConfig.network.reconnect_timeout_ms = MQTT_RECONNECT_INTERVAL;
#else
    mqttConfig.uri = MQTT_BROKER_URI;
    mqttConfig.cert_pem = MQTT_ROOT_CA;
    mqttConfig.client_id = DEVICE_ID;
    mqttConfig.username = MQTT_USERNAME;
    mqttConfig.password = MQTT_PASSWORD;
    mqttConfig.keepalive = 60;
    mqttConfig.reconnect_timeout_ms = MQTT_RECONNECT_INTERVAL;
#endif

    mqttClient = esp_mqtt_client_init(&mqttConfig);
    if (mqttClient == nullptr)
    {
        Serial.println("[MQTT] Client init failed.");
        return;
    }

    esp_mqtt_client_register_event(mqttClient, MQTT_EVENT_ANY, onMqttEvent, nullptr);
    esp_err_t startStatus = esp_mqtt_client_start(mqttClient);

    if (startStatus != ESP_OK)
    {
        Serial.printf("[MQTT] Client start failed: 0x%04X\n", startStatus);
        return;
    }

    Serial.printf("[MQTT] Connecting to %s as %s\n", MQTT_BROKER_URI, DEVICE_ID);
}

void handleMqtt()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return;
    }

    unsigned long now = millis();
    if (now - lastWifiReconnectAttempt >= MQTT_RECONNECT_INTERVAL)
    {
        lastWifiReconnectAttempt = now;
        mqttConnected = false;
        Serial.println("[MQTT] Wi-Fi disconnected. Reconnecting Wi-Fi...");
        WiFi.reconnect();
    }
}

bool publishTelemetry(const SensorData &data)
{
    if (mqttClient == nullptr || !mqttConnected)
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
    doc["key"] = MQTT_DEVICE_KEY;
    doc["timestamp"] = timestamp;
    doc["voltage_v"] = data.voltage;
    doc["current_a"] = data.current / 1000.0f;
    doc["irradiance_wm2"] = estimateIrradianceWm2(data);
    doc["temp_c"] = data.temperature;
    doc["yaw_angle_deg"] = getCurrentYawAngle();
    doc["status"] = getMotorStatus();

    char payload[320];
    size_t payloadLength = serializeJson(doc, payload, sizeof(payload));
    if (payloadLength == 0 || payloadLength >= sizeof(payload))
    {
        Serial.println("[MQTT] Telemetry serialization failed or payload is too large.");
        return false;
    }

    String topic = telemetryTopic();
    int messageId = esp_mqtt_client_publish(mqttClient, topic.c_str(), payload, payloadLength, 1, 0);

    if (messageId >= 0)
    {
        Serial.printf("[MQTT] Telemetry queued to %s, msg_id=%d, bytes=%u\n",
                      topic.c_str(), messageId, (unsigned int)payloadLength);
        return true;
    }

    Serial.println("[MQTT] Telemetry publish failed.");
    return false;
}

bool isMqttConnected()
{
    return mqttConnected;
}
