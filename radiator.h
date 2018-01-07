#ifndef RADIATOR_H
#define RADIATOR_H

#include <Arduino.h>

#define RADIATOR_COUNT      3

struct radiator_s {
    float SetPoint;
    float Temperature;
};

#endif // RADIATOR_H
