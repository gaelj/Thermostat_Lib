#ifndef RADIATOR_H
#define RADIATOR_H

#include <Arduino.h>

struct radiator_s {
    byte baseSetPoint;
    byte floatSetPoint;
    float SetPoint;

    byte baseTemperature;
    byte floatTemperature;
    float Temperature;
};

#endif // RADIATOR_H
