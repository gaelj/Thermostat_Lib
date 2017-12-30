/**
 * @brief Main Thermostat class
 *          Gives access to desired temperature, real temperature & humidity
 *
 */

#include "thermo_control.h"

TimerClass BOILER_ON_TIMER(0);
TimerClass PID_TIMER(BOILER_MIN_TIME);
float LastOutput;
float newOutput;
float setPoint;
ThermostatMode CurrentThermostatMode;


 /**
  * @brief Constructor. Turns the boiler off
  *
  */
void Thermostat_Init()
{
    PID_TIMER.DurationInMillis = TheSettings.SampleTime;
    SetBoilerState(SWITCH_OFF);
    LastOutput = 0;
    PIDREG.Create(SensorTemperature, 0, 1, &SensorTemperature, &setPoint);
    PIDREG.SetMode(AUTOMATIC);
    CurrentThermostatMode = Prm.CurrentThermostatMode;
}

/**
 * @brief Main loop function
 *
 * @return int      0 if OK, -1 in case of error
 */
void Thermostat_Loop()
{
    // Turn off boiler if setpoint is reached
    if (SensorTemperature < setPoint)
        BOILER_ON_TIMER.IsActive = false;

    // Set mode if changed
    if (Prm.CurrentThermostatMode != CurrentThermostatMode) {
        CurrentThermostatMode = Prm.CurrentThermostatMode;
        PID_TIMER.IsActive = false;
    }

    setPoint = Settings_GetSetPoint(Prm.CurrentThermostatMode);

    if (PID_TIMER.IsElapsedRestart()) {
        newOutput = PIDREG.Compute();
        if (newOutput != -1)
            LastOutput = newOutput;
        if (LastOutput > 0) {
            BOILER_ON_TIMER.DurationInMillis = TheSettings.SampleTime * LastOutput;
            BOILER_ON_TIMER.Start();
        }
    }
    
    SetBoilerState(BOILER_ON_TIMER.IsElapsed() ? SWITCH_OFF : SWITCH_ON);
}
