/*
 Name:		ThermostatRemoteConfig.h
 Created:	24/12/2017 22:00:55
 Author:	gael
 Editor:	http://www.visualmicro.com
*/

#ifndef REMOTECONFIG_H
#define REMOTECONFIG_H

#include <Arduino.h>
#include "globals.h"
#include "enumerations.h"
#include "zwave_encoding.h"
#include "timer.h"

#define NO_VALUE        0xFF

void Remote_InitParameters();
void Remote_ProcessCommandValue(Commands command, byte value);

#endif // REMOTECONFIG_H
