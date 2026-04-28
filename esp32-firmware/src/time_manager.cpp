#include <Arduino.h>
#include <time.h>
#include "time_manager.h"
#include "config.h"

void initClock() {
    Serial.printf("Synchronizing time from: %s, %s\n", NTP_SERVER_1, NTP_SERVER_2);
    
    configTzTime(TIME_ZONE, NTP_SERVER_1, NTP_SERVER_2);

    struct tm timeinfo;
    int retry = 0;
    while (!getLocalTime(&timeinfo) && retry < 10) {
        Serial.print(".");
        delay(1000);
        retry++;
    }

        if (retry < 10) {
        Serial.println("\n--- Time synchronized succesfully ---");
        printCurrentTime();
    } else {
        Serial.println("\n--- ERROR --- Time not synchronized ---");
    }
}

unsigned long getUnixTime() {
    time_t now;
    time(&now);
    return now;
}

void printCurrentTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Time not synchronized.");
        return;
    }

    Serial.printf("Actual date and time: %04d-%02d-%02d %02d:%02d:%02d\n",
                  timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
                  timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
}