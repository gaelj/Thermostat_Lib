#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

#include <Arduino.h>

#define THERMOSTAT_MODE_COUNT 6

/**
* @brief Possible modes for the thermostat
*
*/
enum ThermostatMode {
    NoMode,
    Frost,
    Absent,
    Night,
    Day,
    Warm
};

/**
* @brief Structure containing all settings persisted to EEPROM
*
*/
struct settings_s {
    byte Version;
    float CurrentSetPoint;
    float Setpoint_Frost;
    float Setpoint_Absent;
    float Setpoint_Night;
    float Setpoint_Day;
    float Setpoint_Warm;
    float Kp;                  // (P)roportional Tuning Parameter
    float Ki;                  // (I)ntegral Tuning Parameter
    float Kd;                  // (D)erivative Tuning Parameter
    unsigned long SampleTime;  // The time between 2 measurements
    /*
    float HysteresisRange;     // The number of degrees below setpoint at which heating is set
    float ATuneStep;
    float ATuneNoise;
    float ATuneStartValue;
    float ATuneLookBack;
    */
    byte crc8;
};
typedef struct settings_s settings_t;

struct zwave_values_s {
    byte BoilerState;
    byte Setpoint;
    byte Mode;
    byte ExteriorTemperature;
    byte ExteriorHumidity;
    byte ExteriorPressure;
    word SensorTemperature;
    word SensorHumidity;
};
typedef struct zwave_values_s zwave_values_t;

/**
* @brief Structure containing all global parameters
*
*/
struct params_s {
    ThermostatMode CurrentThermostatMode;
    float ExteriorTemperature;
    float ExteriorHumidity;
    float ExteriorPressure;
    float TempDelta;
    bool IlluminationPower;
};
typedef struct params_s params_t;

#endif // ENUMERATIONS_H
