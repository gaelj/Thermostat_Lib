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
#include "radiator.h"

#define NO_VALUE        0xFF
#define TIMEOUT_DELAY   1000

enum Commands {
    No_Command,                  // 0

    // Get commands: PC sends value to Zuno / Zuno requests value from PC
    Get_Mode,                    // 1

    Get_Radiator0Setpoint1,      // 2
    Get_Radiator0Setpoint2,      // 3
    Get_Radiator0Temperature1,   // 4
    Get_Radiator0Temperature2,   // 5

    Get_Radiator1Setpoint1,      // 6
    Get_Radiator1Setpoint2,      // 7
    Get_Radiator1Temperature1,   // 8
    Get_Radiator1Temperature2,   // 9

    Get_Radiator2Setpoint1,      // 10
    Get_Radiator2Setpoint2,      // 11
    Get_Radiator2Temperature1,   // 12
    Get_Radiator2Temperature2,   // 13

    Get_Radiator3Setpoint1,      // 14
    Get_Radiator3Setpoint2,      // 15
    Get_Radiator3Temperature1,   // 16
    Get_Radiator3Temperature2,   // 17

    Get_Radiator4Setpoint1,      // 18
    Get_Radiator4Setpoint2,      // 19
    Get_Radiator4Temperature1,   // 20
    Get_Radiator4Temperature2,   // 21

    Get_Radiator5Setpoint1,      // 22
    Get_Radiator5Setpoint2,      // 23
    Get_Radiator5Temperature1,   // 24
    Get_Radiator5Temperature2,   // 25

    Get_ExteriorTemperature1,    // 26
    Get_ExteriorTemperature2,    // 27

    Get_ExteriorHumidity1,       // 28
    Get_ExteriorHumidity2,       // 29

    Get_ExteriorPressure1,       // 30
    Get_ExteriorPressure2,       // 31

    // Set commands: Zuno sends value to PC
    Set_Mode,                    // 32

    Set_ActiveRadiator,          // 33

    Set_Radiator0Setpoint1,      // 34
    Set_Radiator0Setpoint2,      // 35

    Set_Radiator1Setpoint1,      // 36
    Set_Radiator1Setpoint2,      // 37

    Set_Radiator2Setpoint1,      // 38
    Set_Radiator2Setpoint2,      // 39

    Set_Radiator3Setpoint1,      // 40
    Set_Radiator3Setpoint2,      // 41

    Set_Radiator4Setpoint1,      // 42
    Set_Radiator4Setpoint2,      // 43

    Set_Radiator5Setpoint1,      // 44
    Set_Radiator5Setpoint2       // 45
};

void Remote_InitParameters();
void Remote_SetCommand(Commands command);
void Remote_SetValue(byte value);

#endif // REMOTECONFIG_H
