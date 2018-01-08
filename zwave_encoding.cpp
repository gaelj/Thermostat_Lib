#include "zwave_encoding.h"



/**
* @brief Encode a real temperature to a value from 0 to 100
*
* @param temp   real temperature (float). Precision of 0.5°C. Must be between -25°C and +24°C (100 values)
*
* @return byte ranging from 0 to 100
*/
byte EncodeTemp(const float temp)
{
    int value = round((temp + 25) * 2);
    if (value < 0) value = 0;
    if (value > 99) value = 99;
    return byte(value);
}

/**
* @brief Decode a byte value from 0 to 100 to a real temperature
*
* @param encoded   encoded temperature (byte)
*
* @return float
*/
float DecodeTemp(const byte encoded)
{
    return (float(encoded) / 2.0f) - 25.0f;
}

float DecodeHumidity(const byte encoded)
{
    return encoded == 99 ? 100.0f : float(encoded);
}

float DecodePressure(const byte encoded)
{
    return 950.0f + float(encoded);
}

/**
* @brief Convert a temperature or humidity sensor reading to byte value for Zwave report
*
*/
word EncodeSensorReading(const float value)
{
    return word(value * 100);
}

float MillisToSeconds(unsigned long m)
{
    return float(m / 100) / 10;
}

float MillisToMinutes(unsigned long m)
{
    return float(m / 1000) / 60;
}
