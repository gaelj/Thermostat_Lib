#ifndef SENSOR_H
#define SENSOR_H

// Select the used hardware here
#undef  TEMP_DS18B20
#define TEMP_DHT

#include <Arduino.h>
#include "pinout.h"
#include "globals.h"

#ifdef TEMP_DHT
#include <ZUNO_DHT.h>
#define FORCE_READ      1
#endif

#ifdef TEMP_DS18B20
#include <ZUNO_OneWire.h>
#include <ZUNO_DS18B20.h>
#define DS18B20_ROM_SIZE 8
#define DS18B20_MAX_SENSOR 1
#endif

void InitSensor();
void ReadSensor();

#endif // SENSOR_H
