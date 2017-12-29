#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

#include <Arduino.h>

#define THERMOSTAT_MODE_COUNT 5

/**
* @brief Possible modes for the thermostat
*
*/
enum ThermostatMode {
    Frost = 0,
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
    byte  crc8;
};

/**
* @brief Structure containing all global parameters
*
*/
struct params_s {
    ThermostatMode CurrentThermostatMode;
    byte RadiatorCount;
    byte ActiveRadiator;
    float RadiatorSetpoint;
    float RadiatorTemperature;

    float baseExteriorTemperature;
    float floatExteriorTemperature;
    float ExteriorTemperature;

    float baseExteriorHumidity;
    float floatExteriorHumidity;
    float ExteriorHumidity;

    float ExteriorPressure;

    float TempDelta;

    bool IlluminationPower;
};

#endif // ENUMERATIONS_H
