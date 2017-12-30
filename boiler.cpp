/**
 * @brief Boiler class
 *          Gives access to boiler state
 * 
 */

#include "boiler.h"

TimerClass SAFETY_TIMER(BOILER_MIN_TIME);
bool CurrentBoilerState = SWITCH_ON; // inital ON to allow forced OFF at startup

/**
 * @brief Set the state of the boiler to on or off, unless the last state change was too recent
 * 
 * @param value     the desired state
 */
void SetBoilerState(byte value)
{
    if (CurrentBoilerState != value && SAFETY_TIMER.IsElapsedRestart()) {
        CurrentBoilerState = value;
        zunoSendToGroupSetValueCommand(CONTROL_GROUP_1, value);
    }
}
