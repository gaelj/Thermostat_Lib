#include "timer.h"

TimerClass::TimerClass(unsigned long durationInMillis)
{
    DurationInMillis = durationInMillis;
    StartTime = millis();
    IsActive = false;
}

void TimerClass::Start()
{
    StartTime = millis();
    IsActive = true;
}

bool TimerClass::IsElapsed()
{
    GetProgress();
    if (!IsActive || GetCurrentDuration() >= DurationInMillis) {
        IsActive = false;
        return true;
    }
    return false;
}

bool TimerClass::IsElapsedRestart()
{
    if (IsElapsed()) {
        Start();
        return true;
    }
    return false;
}

void TimerClass::GetProgress()
{
    Duration = MillisToMinutes(DurationInMillis);
    unsigned long currentDurationInMillis = GetCurrentDuration();
    float currentDurationSec = float(currentDurationInMillis) / 10;
    float totalDurationSec = float(DurationInMillis) / 1000;
    Progress = round(currentDurationSec / totalDurationSec);
}

unsigned long TimerClass::GetCurrentDuration()
{
    return millis() - StartTime;
}
