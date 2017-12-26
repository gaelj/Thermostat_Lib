#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
#include "zwave_encoding.h"

class TimerClass {
public:
    TimerClass(unsigned long durationInMillis);
    void Start();
    bool IsElapsedRestart();
    bool IsElapsed();
    bool IsActive;
    unsigned long DurationInMillis;
    float Duration;
    unsigned long StartTime;
    float Progress;
    unsigned long GetCurrentDuration();
    void GetProgress();
};

#endif // TIMER_H
