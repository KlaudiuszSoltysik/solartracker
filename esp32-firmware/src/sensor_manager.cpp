#include "sensor_manager.h"
#include "config.h"

// I2C definition
TwoWire I2C_0 = TwoWire(0);
TwoWire I2C_1 = TwoWire(1);

// sensor objects definition
Adafruit_INA219 ina219(ADDR_INA219);
Adafruit_TSL2591 tslLeft = Adafruit_TSL2591(1);  // ID 1
Adafruit_TSL2591 tslRight = Adafruit_TSL2591(2); // ID 2
DHT dht(PIN_DHT_DATA, DHT22);

void initSensors() {
    // I2C init
    I2C_0.begin(I2C0_SDA, I2C0_SCL, 100000);
    I2C_1.begin(I2C1_SDA, I2C1_SCL, 100000);

    // sensors init
    if (!ina219.begin(&I2C_0)) {
        Serial.println("INA219 not found");
    }

    if (tslLeft.begin(&I2C_0)) {
    tslLeft.setGain(TSL2591_GAIN_MED);
    tslLeft.setTiming(TSL2591_INTEGRATIONTIME_100MS);
    } else {
        Serial.println("Left TSL2591 not found");
    }

    if (tslRight.begin(&I2C_1)) {
    tslRight.setGain(TSL2591_GAIN_MED);
    tslRight.setTiming(TSL2591_INTEGRATIONTIME_100MS);
    } else {
        Serial.println("Right TSL2591 not found");
    }

    dht.begin(); 

    Serial.println("--- Sensors initialization finished ---");
}

SensorData readAllSensors() {
    SensorData data;

    data.voltage = ina219.getBusVoltage_V();
    data.current = ina219.getCurrent_mA();
    data.power   = ina219.getPower_mW();

    data.temperature = dht.readTemperature();
    data.humidity    = dht.readHumidity();

    // Read and calculate luminosity 
    uint32_t lumL = tslLeft.getFullLuminosity();
    uint32_t lumR = tslRight.getFullLuminosity();
    data.luxLeft  = tslLeft.calculateLux(lumL & 0xFFFF, lumL >> 16);
    data.luxRight = tslRight.calculateLux(lumR & 0xFFFF, lumR >> 16);

    return data;
}