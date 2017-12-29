#ifndef GLOBALS_H
#define GLOBALS_H

#include "enumerations.h"
#include "timer.h"

extern float SensorTemperature;
extern float SensorHumidity;
extern settings_s TheSettings;
extern bool CurrentBoilerState;
extern params_s Prm;
extern TimerClass BOILER_ON_TIMER;
extern TimerClass PID_TIMER;

#endif // GLOBALS_H