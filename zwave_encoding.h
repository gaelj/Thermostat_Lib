/**
* @brief Functions to encode / decode ZWave data
*
*/

#ifndef ZWAVE_ENCODING_H
#define ZWAVE_ENCODING_H

#include <Arduino.h>
#include "enumerations.h"

byte EncodeMode(const ThermostatMode mode);
ThermostatMode DecodeMode(const byte code);
byte EncodeExteriorTemperature(const float temp);
float DecodeExteriorTemperature(const byte encoded);
word EncodeSensorReading(const float value);
float MillisToMinutes(unsigned long m);
float MillisToSeconds(unsigned long m);
float CalculateTemperature(byte baseVal, byte floatVal);

#endif // ZWAVE_ENCODING_H
