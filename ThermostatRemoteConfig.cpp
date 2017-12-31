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

    for (byte i = 0; i < 6; i++) {
        Radiators[i].SetPoint = 0;
        Radiators[i].Temperature = 0;
    }
}

byte GetRadId(byte commandBase)
{
    return (currentCommand - commandBase) / 4;
}

void ProcessCommandValue()
{
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

            case Get_Radiator0Setpoint1:
            case Get_Radiator1Setpoint1:
            case Get_Radiator2Setpoint1:
            case Get_Radiator3Setpoint1:
            case Get_Radiator4Setpoint1:
            case Get_Radiator5Setpoint1:
                radiatorId = GetRadId(Get_Radiator0Setpoint1);
                Radiators[radiatorId].SetPoint = float(currentValue) - 50.0f;
                break;
            case Get_Radiator0Setpoint2:
            case Get_Radiator1Setpoint2:
            case Get_Radiator2Setpoint2:
            case Get_Radiator3Setpoint2:
            case Get_Radiator4Setpoint2:
            case Get_Radiator5Setpoint2:
                radiatorId = GetRadId(Get_Radiator0Setpoint2);
                Radiators[radiatorId].SetPoint += float(currentValue) / 100.0f;
                break;

            case Get_Radiator0Temperature1:
            case Get_Radiator1Temperature1:
            case Get_Radiator2Temperature1:
            case Get_Radiator3Temperature1:
            case Get_Radiator4Temperature1:
            case Get_Radiator5Temperature1:
                radiatorId = GetRadId(Get_Radiator0Temperature1);
                Radiators[radiatorId].Temperature = float(currentValue) - 50.0f;
                break;
            case Get_Radiator0Temperature2:
            case Get_Radiator1Temperature2:
            case Get_Radiator2Temperature2:
            case Get_Radiator3Temperature2:
            case Get_Radiator4Temperature2:
            case Get_Radiator5Temperature2:
                radiatorId = GetRadId(Get_Radiator0Temperature2);
                Radiators[radiatorId].Temperature += float(currentValue) / 100.0f;
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

void Remote_SetCommand(Commands command)
{
    currentCommand = command;
}

void Remote_SetValue(byte value)
{
    currentValue = value;
    ProcessCommandValue();
}
