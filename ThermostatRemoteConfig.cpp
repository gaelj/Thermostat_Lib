/*
 Name:		ThermostatRemoteConfig.cpp
 Created:	24/12/2017 22:00:55
 Author:	gael
 Editor:	http://www.visualmicro.com
*/

#include "ThermostatRemoteConfig.h"

Commands currentCommand = No_Command;
byte currentValue = NO_VALUE;

void Remote_InitParameters()
{
    Prm.CurrentThermostatMode = Absent;
    Prm.ExteriorTemperature = 0;
    Prm.ExteriorHumidity = 0;
    Prm.IlluminationPower = true;
}

byte GetRadId(byte commandBase)
{
    return (currentCommand - commandBase) / 4;
}

void Remote_ProcessCommandValue(Commands command, byte value)
{
    currentCommand = command;
    currentValue = value;

#ifdef LOGGING_ACTIVE
    Serial.print(millis());
    Serial.print(" Processing cmd: ");
    Serial.print(currentCommand);
    Serial.print(" value: ");
    Serial.print(currentValue);
#endif // LOGGING_ACTIVE

    if (currentCommand != No_Command && currentValue != NO_VALUE) {
        byte radiatorId = 0xFF;

        switch (currentCommand) {
            case Get_Mode:
                Prm.CurrentThermostatMode = DecodeMode(currentValue);
                break;

            case Get_ExteriorTemperature1:
                Prm.ExteriorTemperature = float(currentValue) - 50.0f;
                break;
            case Get_ExteriorTemperature2:
                Prm.ExteriorTemperature += float(currentValue) / 100.0f;
                break;

            case Get_ExteriorHumidity:
                Prm.ExteriorHumidity = float(currentValue);
                break;

            case Get_ExteriorPressure:
                Prm.ExteriorPressure = float(currentValue) + 950.0f;
                break;
        }
#ifdef LOGGING_ACTIVE
        Serial.println(" OK");
#endif // LOGGING_ACTIVE
    }
#ifdef LOGGING_ACTIVE
    else {
        Serial.println(" NG");
    }
#endif // LOGGING_ACTIVE
}
