#ifndef BOILER_H
#define BOILER_H

#include <Arduino.h>
#include "globals.h"
#include <ZUNO_legacy_channels.h>
#include <ZUNO_channels.h>
#include <ZUNO_Definitions.h>
#include "settings.h"
#include "timer.h"

#define SWITCH_ON           0xFF
#define SWITCH_OFF          0x00

#define CONTROL_GROUP_1     1  // Boiler group

void SetBoilerState(byte value);

#endif // BOILER_H
