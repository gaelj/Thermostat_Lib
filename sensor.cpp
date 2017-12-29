/**
 * @brief Main Thermostat class
 *          Gives access to boiler state, desired temperature, real temperature & humidity,
 *          and implements ZWave getter & setter functions
 * 
 */

#include "sensor.h"

float SensorTemperature = -0.2;
float SensorHumidity = -0.2;

#ifdef TEMP_DHT

DHT DhtSensor(PIN_TEMP_SENSOR, DHT22);

/**
 * @brief Constructor. Does required initialisations and turns the boiler off
 * 
 */
void InitSensor()
{
    DhtSensor.begin();
    ReadSensor();
}

/**
 * @brief Read the sensor and store the result to buffer
 * 
 */
void ReadSensor()
{
    do {
        SensorTemperature = DhtSensor.readTemperature(FORCE_READ);
    } while (SensorTemperature == -0.1);
    do {
        SensorHumidity = DhtSensor.readHumidity(FORCE_READ);
    } while (SensorHumidity == -0.1);
}
#endif




#ifdef TEMP_DS18B20

OneWire ow(PIN_TEMP_SENSOR);
DS18B20Sensor ds18b20(&ow);

byte sensor_roms[DS18B20_ROM_SIZE * DS18B20_MAX_SENSOR];
#define DS18B20_ROM_DATA(index) (&sensor_roms[index * DS18B20_ROM_SIZE])

/**
 * @brief Constructor. Does required initialisations and turns the boiler off
 * 
 */
void InitSensor()
{
    ds18b20.findAllSensors(sensor_roms);
    ReadSensor();
}

/**
 * @brief Read the sensor and store the result to buffer
 * 
 */
void ReadSensor()
{
    Temperature = ds18b20.getTemperature(DS18B20_ROM_DATA(0));
}
#endif
