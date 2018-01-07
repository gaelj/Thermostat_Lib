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
float inputTemperature;
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
    PIDREG.Create(SensorTemperature, 0, 1, &inputTemperature, &setPoint);
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
    // Set mode if changed
    if (Prm.CurrentThermostatMode != CurrentThermostatMode) {
        CurrentThermostatMode = Prm.CurrentThermostatMode;
        PID_TIMER.IsActive = false;
    }

    // Compute the PID and set boiler duration accordingly
    if (PID_TIMER.IsElapsedRestart()) {

        // Get the temperature & setpoint with the largest delta on thermostat & each radiator
        setPoint = Settings_GetSetPoint(Prm.CurrentThermostatMode);
        inputTemperature = SensorTemperature;

        newOutput = PIDREG.Compute();
        if (newOutput != -1)
            LastOutput = newOutput;
        BOILER_ON_TIMER.DurationInMillis = TheSettings.SampleTime * MIN(MAX(LastOutput, 0.0f), 1.0f);
        BOILER_ON_TIMER.Start();
    }

    // Turn off boiler if setpoint is reached
    if (inputTemperature > setPoint)
        BOILER_ON_TIMER.IsActive = false;
    
    // Change boiler state if requried
    SetBoilerState(BOILER_ON_TIMER.IsElapsed() ? SWITCH_OFF : SWITCH_ON);
}
