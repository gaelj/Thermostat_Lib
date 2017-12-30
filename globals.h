#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include "enumerations.h"
#include "timer.h"
#include "radiator.h"
#include "PID_v1.h"

extern float SensorTemperature;
extern float SensorHumidity;
extern settings_s TheSettings;
extern bool CurrentBoilerState;
extern params_s Prm;
extern TimerClass BOILER_ON_TIMER;
extern TimerClass PID_TIMER;

extern byte ztxCommand;
extern byte ztxValue;
extern byte zrxCommand;
extern byte zrxValue;

extern radiator_s Radiators[6];

#endif // GLOBALS_H
