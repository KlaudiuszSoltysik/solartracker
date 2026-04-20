#include <WiFi.h>
#include "wifi_manager.h"
#include "config.h"

void setupWifi() {
    Serial.print("Connecting To Wi-Fi: ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\n--- Connected! ---");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}