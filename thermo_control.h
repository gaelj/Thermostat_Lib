#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <Arduino.h>
#include "settings.h"
#include "sensor.h"
#include "boiler.h"
#include "PID_v1.h"
#include "enumerations.h"
#include "timer.h"
#include "ThermostatRemoteConfig.h"
#include "zwave_communication.h"

class ThermostatClass {
public:
    ThermostatClass(PID*, SettingsClass*, SensorClass*, BoilerClass*, TimerClass*, TimerClass*, RemoteConfiguratorClass*, ZwaveCommunicationClass*);
    void Loop();
    TimerClass* BOILER_ON_TIMER;
    TimerClass* PID_TIMER;

private:
    SettingsClass* SETTINGS;
    SensorClass* SENSOR;
    BoilerClass* BOILER;
    RemoteConfiguratorClass* REMOTE;
    ZwaveCommunicationClass* ZWAVE;
    PID* PIDREG;
    float LastOutput;
    ThermostatMode CurrentThermostatMode;
};

#endif // THERMOSTAT_H
