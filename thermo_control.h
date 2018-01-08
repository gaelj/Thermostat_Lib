#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <Arduino.h>
#include <ZUNO_Definitions.h>
#include "globals.h"
#include "settings.h"
#include "sensor.h"
#include "boiler.h"
#include "PID_v1.h"
#include "enumerations.h"
#include "timer.h"

void Thermostat_Init();
void Thermostat_Loop();
void Thermostat_SetMode(ThermostatMode newMode);
void Thermostat_SetSetPoint(float value);

#endif // THERMOSTAT_H
