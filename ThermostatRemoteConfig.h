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
#define TIMEOUT_DELAY   500

enum Commands {
    No_Command,                 // 0

    // Set commands: PC sends value to Zuno / Zuno requests value from PC

    Get_Mode,                   // 1

    Get_Radiator_Count,         // 2
    Get_ActiveRadiator,         // 3

    Get_RadiatorSetpoint1,      // 4
    Get_RadiatorSetpoint2,      // 5

    Get_RadiatorTemperature1,   // 6
    Get_RadiatorTemperature2,   // 7

    Get_ExteriorTemperature1,   // 8
    Get_ExteriorTemperature2,   // 9

    Get_ExteriorHumidity1,      // 10
    Get_ExteriorHumidity2,      // 11

    Get_ExteriorPressure1,      // 12
    Get_ExteriorPressure2,      // 13

    // Get commands: Zuno sends value to PC

    Set_Mode,                   // 14

    Set_ActiveRadiator,         // 15

    Set_RadiatorSetpoint1,      // 16
    Set_RadiatorSetpoint2       // 17

};

void Remote_InitParameters();
void Remote_SetCommand(Commands command);
void Remote_SetValue(byte value);

#endif // REMOTECONFIG_H
