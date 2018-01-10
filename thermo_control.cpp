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
float inputTemperature;


 /**
  * @brief Constructor. Turns the boiler off
  *
  */
void Thermostat_Init()
{
    PID_TIMER.DurationInMillis = TheSettings.SampleTime;
    SetBoilerState(SWITCH_OFF);
    LastOutput = 0;
    PIDREG.Create(SensorTemperature, 0, 1, &inputTemperature, &TheSettings.CurrentSetPoint);
    PIDREG.SetMode(AUTOMATIC);
    Prm.CurrentThermostatMode = NoMode;
}

void Thermostat_SetMode(ThermostatMode newMode)
{
    if (Prm.CurrentThermostatMode == newMode || newMode == NoMode)
        return;
    Prm.CurrentThermostatMode = newMode;
    Thermostat_SetSetPoint(Settings_GetSetPoint(newMode));
}

void Thermostat_SetSetPoint(float value)
{
    if (TheSettings.CurrentSetPoint == value)
        return;
    TheSettings.CurrentSetPoint = value;
    PID_TIMER.IsActive = false;
    zwave_values.Setpoint = EncodeTemp(TheSettings.CurrentSetPoint);
    zunoSendReport(ZUNO_REPORT_SETPOINT);
}

/**
 * @brief Main loop function
 *
 * @return int      0 if OK, -1 in case of error
 */
void Thermostat_Loop()
{
    // Compute the PID and set boiler duration accordingly
    if (PID_TIMER.IsElapsedRestart()) {
        inputTemperature = SensorTemperature;
        newOutput = PIDREG.Compute();
        if (newOutput != -1)
            LastOutput = newOutput;
        BOILER_ON_TIMER.DurationInMillis = TheSettings.SampleTime * MIN(MAX(LastOutput, 0.0f), 1.0f);
        BOILER_ON_TIMER.Start();
    }

    // Turn off boiler if setpoint is reached
    if (inputTemperature > TheSettings.CurrentSetPoint)
        BOILER_ON_TIMER.IsActive = false;
    
    // Change boiler state if requried
    SetBoilerState(BOILER_ON_TIMER.IsElapsed() ? 0 : 99);
}
