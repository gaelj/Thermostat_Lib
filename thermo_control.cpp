/**
 * @brief Main Thermostat class
 *          Gives access to desired temperature, real temperature & humidity
 *
 */

#include "thermo_control.h"

 /**
  * @brief Constructor. Turns the boiler off
  *
  */
ThermostatClass::ThermostatClass(PID* pid, SettingsClass* settings, SensorClass* sensor, BoilerClass* boiler,
    TimerClass* pidTimer, TimerClass* boilerTimer, RemoteConfiguratorClass* remote, ZwaveCommunicationClass* zwave) :
    PIDREG(pid), SETTINGS(settings), SENSOR(sensor), BOILER(boiler), PID_TIMER(pidTimer), BOILER_ON_TIMER(boilerTimer),
    REMOTE(remote), ZWAVE(zwave)
{
    PID_TIMER->DurationInMillis = SETTINGS->TheSettings->SampleTime;
    BOILER->SetBoilerState(SWITCH_OFF);
    LastOutput = 0;
    PIDREG->Create(SENSOR->Temperature, 0, 1);
    PIDREG->SetMode(AUTOMATIC);
    CurrentThermostatMode = REMOTE->CurrentThermostatMode;

}

/**
 * @brief Main loop function
 *
 * @return int      0 if OK, -1 in case of error
 */
void ThermostatClass::Loop()
{
    // Set mode if changed
    if (REMOTE->CurrentThermostatMode != CurrentThermostatMode) {
        CurrentThermostatMode = REMOTE->CurrentThermostatMode;
        PID_TIMER->IsActive = false;
    }

    float temp = SENSOR->Temperature;
    float setPoint = SETTINGS->GetSetPoint(REMOTE->CurrentThermostatMode);

    if (PID_TIMER->IsElapsedRestart()) {

        float newOutput = PIDREG->Compute(temp, setPoint);
        if (newOutput != -1)
            LastOutput = newOutput;
        if (LastOutput > 0) {
            BOILER_ON_TIMER->DurationInMillis = SETTINGS->TheSettings->SampleTime * LastOutput;
            BOILER_ON_TIMER->Start(0);
        }
    }
    BOILER->SetBoilerState((!BOILER_ON_TIMER->IsElapsed() && (temp < setPoint)) ? SWITCH_ON : SWITCH_OFF);
}
