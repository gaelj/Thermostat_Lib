/**
 * @brief Boiler class
 *          Gives access to boiler state
 * 
 */

#include "boiler.h"

TimerClass SAFETY_TIMER(BOILER_MIN_TIME);
byte CurrentBoilerState = SWITCH_ON; // inital ON to allow forced OFF at startup

/**
 * @brief Set the state of the boiler to on or off, unless the last state change was too recent
 * 
 * @param value     the desired state
 */
void SetBoilerState(byte value)
{
    if (CurrentBoilerState != value && SAFETY_TIMER.IsElapsedRestart()) {
#ifdef LOGGING_ACTIVE
        Serial.print("Set boiler: ");
        Serial.println(value);
#endif // LOGGING_ACTIVE

        CurrentBoilerState = value;
        zunoSendToGroupSetValueCommand(CONTROL_GROUP_1, value > 0 ? 0xFF : 00);
    }
    if (zwave_values.BoilerState != CurrentBoilerState) {
#ifdef LOGGING_ACTIVE
        Serial.print("Z SB: ");
        Serial.println(CurrentBoilerState);
#endif // LOGGING_ACTIVE

        zwave_values.BoilerState = CurrentBoilerState;
        zunoSendReport(ZUNO_REPORT_BOILER);
    }
}
