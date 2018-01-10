#include "settings.h"

settings_t TheSettings;

/**
 * @brief Get the selected setpoint temperature
 * 
 */
float Settings_GetSetPoint(const ThermostatMode mode)
{
    switch (mode) {
        case Frost:      return TheSettings.Setpoint_Frost;
        case Absent:     return TheSettings.Setpoint_Absent;
        case Night:      return TheSettings.Setpoint_Night;
        case Day:        return TheSettings.Setpoint_Day;
        case Warm:       return TheSettings.Setpoint_Warm;
        case DayFloor1:  return TheSettings.Setpoint_DayFloor1;
        case WarmFloor1: return TheSettings.Setpoint_WarmFloor1;
        case DayFloor2:  return TheSettings.Setpoint_DayFloor2;
        case WarmFloor2: return TheSettings.Setpoint_WarmFloor2;
        default:         return TheSettings.Setpoint_Absent;
    }
}

/**
* @brief Calculate the CRC8 value of a structure
*
* @param data
* @param count
* @return byte
*/
byte GetCrc8(byte* data, byte count)
{
    byte result = 0xDF;
    while (count--) {
        result ^= *data;
        data++;
    }
    return result;
}

/**
* @brief Restore the settings struct from E2P. Checks the CRC8 and version values. Resets to default values in case of error
*
* @return true   The settings are valid
* @return false  The settings are invalid (wrong CRC or E2P version has changed)
*/
bool Settings_RestoreSettings()
{
    //Serial.println("Restore stgs");
    EEPROM.get(E2P_START_ADDRESS, &TheSettings, sizeof(settings_t));
    Settings_Dump();
    return GetCrc8((byte*)&TheSettings, sizeof(settings_t) - 1) == TheSettings.crc8
            && TheSettings.Version == E2P_VERSION;
}

/**
* @brief Apply default values to TheSettings
*
*/
void Settings_LoadDefaults()
{
    //Serial.println("Reset stgs");
    // Invalid data - reset all
    TheSettings.Version = E2P_VERSION;
    TheSettings.Setpoint_Frost = DEFAULT_Setpoint_Frost;
    TheSettings.Setpoint_Absent = DEFAULT_Setpoint_Absent;
    TheSettings.Setpoint_Night = DEFAULT_Setpoint_Night;
    TheSettings.Setpoint_Day = DEFAULT_Setpoint_Day;
    TheSettings.Setpoint_Warm = DEFAULT_Setpoint_Warm;
    TheSettings.Setpoint_DayFloor1 = DEFAULT_Setpoint_DayFloor1;
    TheSettings.Setpoint_WarmFloor1 = DEFAULT_Setpoint_WarmFloor1;
    TheSettings.Setpoint_DayFloor2 = DEFAULT_Setpoint_DayFloor2;
    TheSettings.Setpoint_WarmFloor2 = DEFAULT_Setpoint_WarmFloor2;
    TheSettings.Kp = DEFAULT_Kp;
    TheSettings.Ki = DEFAULT_Ki;
    TheSettings.Kd = DEFAULT_Kd;
    TheSettings.SampleTime = DEFAULT_SampleTime;
    /*
    _Settings.HysteresisRange = 0.5;
    _Settings.ATuneStep = 50;
    _Settings.ATuneNoise = 1;
    _Settings.ATuneStartValue = 100;
    _Settings.ATuneLookBack = 20;
    */
}

/**
* @brief Calculate the CRC8 and persist the settings struct to E2P
*
*/
bool Settings_PersistSettings()
{
    //Serial.print("Persist stgs ");
    //Serial.println((int)sizeof(settings_s));
    TheSettings.crc8 = GetCrc8((byte*)&TheSettings, sizeof(settings_t) - 1);
    EEPROM.put(E2P_START_ADDRESS, &TheSettings, sizeof(settings_t));
    if (!Settings_RestoreSettings()) {
        //Serial.println("Persist check error");
        return false;
    }
    return true;
}

/**
* @brief Dump all setting values to Serial
*
*/
void Settings_Dump()
{
#ifdef LOGGING_ACTIVE
    //Serial.println("============ Settings:");
    Serial.println(TheSettings.Version);
    Serial.println(TheSettings.Setpoint_Frost);
    Serial.println(TheSettings.Setpoint_Absent);
    Serial.println(TheSettings.Setpoint_Night);
    Serial.println(TheSettings.Setpoint_Day);
    Serial.println(TheSettings.Setpoint_Warm);
    Serial.println(TheSettings.Kp);
    Serial.println(TheSettings.Ki);
    Serial.println(TheSettings.Kd);
    /*
    Serial.println(_Settings.HysteresisRange);
    Serial.println(_Settings.ATuneStep);
    Serial.println(_Settings.ATuneNoise);
    Serial.println(_Settings.ATuneStartValue);
    Serial.println(_Settings.ATuneLookBack);
    */
    Serial.println(TheSettings.SampleTime);
    Serial.println(TheSettings.crc8);
    //Serial.println("============");
#endif // LOGGING_ACTIVE
}
