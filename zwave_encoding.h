/**
* @brief Functions to encode / decode ZWave data
*
*/

#ifndef ZWAVE_ENCODING_H
#define ZWAVE_ENCODING_H

#include <Arduino.h>
#include "enumerations.h"

byte EncodeTemp(const float temp);
float DecodeTemp(const byte encoded);
float DecodeHumidity(const byte encoded);
float DecodePressure(const byte encoded);
word EncodeSensorReading(const float value);
float MillisToMinutes(unsigned long m);
float MillisToSeconds(unsigned long m);

#endif // ZWAVE_ENCODING_H
