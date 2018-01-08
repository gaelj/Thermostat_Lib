#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Arduino.h>
#include "globals.h"
#include "sensor.h"
#include "boiler.h"
#include "thermo_control.h"
#include "enumerations.h"

void LedsSetFlash(byte color);
void LedsSetBlinkingState();
void LedsSetAnimationState();
void LedsDrawAll();

#endif // LED_CONTROL_H
