#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <EEPROM.h>
#include "globals.h"
#include "led.h"
#include "enumerations.h"

//#define LOGGING_ACTIVE
#undef LOGGING_ACTIVE

#define E2P_VERSION                 2           // change this value to apply default settings on first boot after flash
#define E2P_START_ADDRESS           1

#define THERMOSTAT_MIN              5.0         // minimum thermostat setting
#define THERMOSTAT_MAX              25.0        // maximum thermostat setting
#define THERMOSTAT_DEFAULT          18.0        // default thermostat setting

#define BOILER_MIN_TIME             1 * 60000   // min time between boiler state changes

#define LOOP_DELAY                  10          // min loop period (including loop execution time)
#define ZWAVE_LONG_PERIOD           30000       // ZWave refresh period (ZWave spec requires min 30s)
#define ZWAVE_SHORT_PERIOD          4000        // Wait period between zwave send command and read response command & value
#define MODE_SET_DELAY_PERIOD       1000        // Wait delay before setting mode selected by button push (allows cycling through modes and only sending the last selected mode)
#define READ_SENSOR_PERIOD          10000       // temperature sensor refresh period (millis)
#define OLED_PAGE_PERIOD            5000        // time during which each paged is displayed before moving on to the next one
#define LED_BLINK_PERIOD            1500
#define LED_FLASH_PERIOD            100
#define LED_ANIMATION_STEP_PERIOD   250
#define LED_ANIMATION_MIN_PERIOD    100
#define LED_ANIMATION_MAX_PERIOD    1000
#define LED_ANIMATION_TOTAL_PERIOD  30000
static const byte ColorsByMode[THERMOSTAT_MODE_COUNT] = { COLOR_BLUE, COLOR_CYAN, COLOR_MAGENTA, COLOR_GREEN, COLOR_YELLOW };

#define LED_COUNT                   3
#define FLASHES                     3 // 0-1-0
#define FLASH_QUEUE_LEN             32

#define BOILER_BLINK_COLOR          COLOR_RED
#define SET_SETPOINT_COLOR          COLOR_BLUE
#define GET_SETPOINT_COLOR          COLOR_YELLOW
#define GET_TEMPRATURE_COLOR        COLOR_GREEN
#define ZUNO_CALLBACK_COLOR         COLOR_WHITE

#define DEFAULT_Setpoint_Frost      5.0
#define DEFAULT_Setpoint_Absent     14.0
#define DEFAULT_Setpoint_Night      15.0
#define DEFAULT_Setpoint_Day        19.0
#define DEFAULT_Setpoint_Warm       22.0
#define DEFAULT_Kp                  0.5
#define DEFAULT_Ki                  0.0
#define DEFAULT_Kd                  0.0
#define DEFAULT_SampleTime          10 * 60000

/**
 * @brief Access to the settings
 */
float Settings_GetSetPoint(const ThermostatMode mode);
bool Settings_RestoreSettings();
bool Settings_PersistSettings();
void Settings_LoadDefaults();
void Settings_Dump();

#endif // SETTINGS_H
