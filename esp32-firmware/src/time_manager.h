#pragma once

#include <Arduino.h>

// Get NTP time and set ESP32 system clock
void initClock();

// Returns the current time in UNIX format
unsigned long getUnixTime();

// Print current time in terminal
void printCurrentTime();