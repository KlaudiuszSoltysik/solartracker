#include <Ticker.h>
#include "sensor_manager.h"
#include "config.h"

// I2C definition
TwoWire &I2C_0 = Wire;
TwoWire I2C_1 = TwoWire(1);

// sensor objects definition
INA226 ina226(ADDR_INA226, &I2C_0);
Adafruit_TSL2591 tslLeft = Adafruit_TSL2591(1);  // ID 1
Adafruit_TSL2591 tslRight = Adafruit_TSL2591(2); // ID 2
Adafruit_BMP280 bmp; // I2C default address 0x76

bool ina226Ready = false;
bool tslLeftReady = false;
bool tslRightReady = false;

Ticker sensorsTimer;
volatile bool _sensorsFlag = false;

void onSensorsTimerTick()
{
    _sensorsFlag = true;
}

bool isTimeToReadSensors()
{
    if (_sensorsFlag)
    {
        _sensorsFlag = false;
        return true;
    }
    return false;
}

void initSensors()
{
    // I2C init
    bool status0 = I2C_0.begin(I2C0_SDA, I2C0_SCL, 100000);
    bool status1 = I2C_1.begin(I2C1_SDA, I2C1_SCL, 100000);

    // sensors init

    if (!status0) Serial.println("Błąd startu magistrali I2C_0");
    if (!status1) Serial.println("Błąd startu magistrali I2C_1");

    if (ina226.begin())
    {
        int calibrationStatus = ina226.setMaxCurrentShunt(INA226_MAX_CURRENT_A, INA226_SHUNT_OHMS);
        if (calibrationStatus == INA226_ERR_NONE)
        {
            ina226Ready = true;
        }
        else
        {
            Serial.printf("INA226 calibration failed: 0x%04X\n", calibrationStatus);
        }
    }
    else
    {
        Serial.println("INA226 not found");
    }

    if (tslLeft.begin(&I2C_0))
    {
        tslLeftReady = true;
        tslLeft.setGain(TSL2591_GAIN_LOW);
        tslLeft.setTiming(TSL2591_INTEGRATIONTIME_100MS);
    }
    else
    {
        Serial.println("Left TSL2591 not found");
    }

        if (!bmp.begin(0x76))
    {
        Serial.println("BMP280 not found");
    }

    if (tslRight.begin(&I2C_1))
    {
        tslRightReady = true;
        tslRight.setGain(TSL2591_GAIN_LOW);
        tslRight.setTiming(TSL2591_INTEGRATIONTIME_100MS);
    }
    else
    {
        Serial.println("Right TSL2591 not found");
    }

    sensorsTimer.attach(SENSORS_READ_INTERVAL, onSensorsTimerTick);
    Serial.println("--- Sensors initialization finished ---");
}

SensorData readAllSensors(bool useSimulation)
{
    SensorData data = {};

    if (useSimulation)
    {
        // Simulated sensor readings with random variations within ranges
        data.voltage = 12.0 + (rand() % 11) / 10.0;      // 12.0 - 13.0V
        data.current = 2.0 + (rand() % 11) / 10.0;       // 2.0 - 3.0mA
        data.power = 25.0 + (rand() % 101) / 10.0;       // 25.0 - 35.0mW
        // data.temperature = 20.0 + (rand() % 121) / 10.0; // 20.0 - 32.0°C
        data.temperature = bmp.readTemperature();
        data.luxLeft = 450.0 + (rand() % 101);           // 450 - 550 lux
        data.luxRight = 430.0 + (rand() % 101);          // 430 - 530 lux
    }
    else
    {
        // Real sensor readings
        if (ina226Ready)
        {
            data.voltage = ina226.getBusVoltage();
            data.current = ina226.getCurrent_mA();
            data.power = ina226.getPower_mW();
        }

        data.temperature = bmp.readTemperature();

        data.luxLeft = 0;
        data.luxRight = 0;

        if (tslLeftReady)
        {
            uint32_t lumL = tslLeft.getFullLuminosity();
            data.luxLeft = tslLeft.calculateLux(lumL & 0xFFFF, lumL >> 16);
        }

        if (tslRightReady)
        {
            uint32_t lumR = tslRight.getFullLuminosity();
            data.luxRight = tslRight.calculateLux(lumR & 0xFFFF, lumR >> 16);
        }
    }

    return data;
}
