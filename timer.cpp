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
    Progress = float(long(100.0f * float(GetCurrentDuration()) / float(DurationInMillis)));
}

unsigned long TimerClass::GetCurrentDuration()
{
    return millis() - StartTime;
}
