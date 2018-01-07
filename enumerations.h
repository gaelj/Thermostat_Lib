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
    float ExteriorTemperature;
    float ExteriorHumidity;
    float ExteriorPressure;
    float TempDelta;
    bool IlluminationPower;
};

#define ZWAVE_MSG_COUNT     5
enum Commands {
    No_Command,                  // 0

    // Get commands: PC sends value to Zuno / Zuno requests value from PC
    Get_Mode,                    // 1

    Get_ExteriorTemperature1,    // 
    Get_ExteriorTemperature2,    // 

    Get_ExteriorHumidity,        // 

    Get_ExteriorPressure,        // 5

    Get_Radiator0Setpoint1,      // 
    Get_Radiator0Setpoint2,      // 
    Get_Radiator0Temperature1,   // 
    Get_Radiator0Temperature2,   // 

    Get_Radiator1Setpoint1,      // 10
    Get_Radiator1Setpoint2,      // 
    Get_Radiator1Temperature1,   // 
    Get_Radiator1Temperature2,   // 

    Get_Radiator2Setpoint1,      // 
    Get_Radiator2Setpoint2,      // 15
    Get_Radiator2Temperature1,   // 
    Get_Radiator2Temperature2,   // 

    Get_Radiator3Setpoint1,      // 
    Get_Radiator3Setpoint2,      // 
    Get_Radiator3Temperature1,   // 20
    Get_Radiator3Temperature2,   // 

    Get_Radiator4Setpoint1,      // 
    Get_Radiator4Setpoint2,      // 
    Get_Radiator4Temperature1,   // 
    Get_Radiator4Temperature2,   // 25

    Get_Radiator5Setpoint1,      // 
    Get_Radiator5Setpoint2,      // 
    Get_Radiator5Temperature1,   // 
    Get_Radiator5Temperature2,   // 29

    // Set commands: Zuno sends value to PC
    Set_Mode,                    // 30

    Set_Radiator0Setpoint1,      // 
    Set_Radiator0Setpoint2,      // 

    Set_Radiator1Setpoint1,      // 
    Set_Radiator1Setpoint2,      // 

    Set_Radiator2Setpoint1,      // 35
    Set_Radiator2Setpoint2,      // 

    Set_Radiator3Setpoint1,      // 
    Set_Radiator3Setpoint2,      // 

    Set_Radiator4Setpoint1,      // 
    Set_Radiator4Setpoint2,      // 40

    Set_Radiator5Setpoint1,      // 
    Set_Radiator5Setpoint2       // 42
};
#endif // ENUMERATIONS_H
