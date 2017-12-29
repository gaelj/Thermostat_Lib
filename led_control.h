#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Arduino.h>
#include "globals.h"
#include "sensor.h"
#include "boiler.h"
#include "thermo_control.h"
#include "enumerations.h"
#include "ThermostatRemoteConfig.h"

class LedControlClass {
public:
    LedControlClass();
    void SetFlash(byte color);
    void SetBlinkingState();
    void SetAnimationState();
    void DrawAll();
    void SetPower(bool value);

private:
    bool ledBlinkState;
    byte ledColors[LED_COUNT];
    byte flashColor;
    byte flashCounter;
    byte flashQueue[FLASH_QUEUE_LEN];
    int animationDirection;
    int animationIndex;
    void StartAnimation(int direction, int period);
    void FlashEnqueue(byte color);
    byte FlashDequeue();
    void DoFlash(byte color);
    byte flashQueueSize;
    bool power;
    float lastTemp;
};

#endif // LED_CONTROL_H
