#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include "enumerations.h"
#include "timer.h"
#include "PID_v1.h"

extern zwave_values_t zwave_values;
extern settings_t TheSettings;
extern params_t Prm;

extern float SensorTemperature;
extern float SensorHumidity;
extern byte CurrentBoilerState;
extern TimerClass BOILER_ON_TIMER;
extern TimerClass PID_TIMER;

extern byte currentPage;

#endif // GLOBALS_H
