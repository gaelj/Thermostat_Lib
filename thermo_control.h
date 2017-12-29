#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <Arduino.h>
#include "globals.h"
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
    ThermostatClass(PID*);
    void Loop();

private:
    PID* PIDREG;
    float LastOutput;
    float newOutput;
    float setPoint;
    ThermostatMode CurrentThermostatMode;
};

#endif // THERMOSTAT_H
