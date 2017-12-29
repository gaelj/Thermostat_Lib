/*
 Name:		ThermostatRemoteConfig.cpp
 Created:	24/12/2017 22:00:55
 Author:	gael
 Editor:	http://www.visualmicro.com
*/

#include "ThermostatRemoteConfig.h"

char* GotCommand = "GC=";
char* GotValue = "GV=";

Commands currentCommand = No_Command;
byte currentValue = NO_VALUE;


void Remote_InitParameters()
{
    Prm.CurrentThermostatMode = Absent;
    Prm.baseExteriorTemperature = 10;
    Prm.floatExteriorTemperature = 0;
    Prm.ExteriorTemperature = 10;

    Prm.baseExteriorHumidity = 0;
    Prm.floatExteriorHumidity = 0;
    Prm.ExteriorHumidity = 0;
}

void ProcessCommandValue()
{
    if (currentCommand != No_Command && currentValue != NO_VALUE) {
        /*
        Serial.print(GotCommand);
        Serial.print(currentCommand);
        Serial.print(GotValue);
        Serial.println(currentValue);*/

        switch (currentCommand) {
            case Get_Mode:
                Prm.CurrentThermostatMode = DecodeMode(currentValue);
                break;

            case Get_Radiator_Count:
                Prm.RadiatorCount = currentValue;
                break;
            case Get_ActiveRadiator:
                Prm.ActiveRadiator = currentValue;
                break;

            case Get_RadiatorSetpoint1:
                Prm.RadiatorSetpoint = currentValue;
                break;
            case Get_RadiatorSetpoint2:
                Prm.RadiatorSetpoint += float(currentValue) / 100;
                break;

            case Get_RadiatorTemperature1:
                Prm.RadiatorTemperature = currentValue;
                break;
            case Get_RadiatorTemperature2:
                Prm.RadiatorTemperature += float(currentValue) / 100;
                break;

            case Get_ExteriorTemperature1:
                Prm.baseExteriorTemperature = currentValue - 50;
                Prm.ExteriorTemperature = Prm.baseExteriorTemperature + Prm.floatExteriorTemperature;
                break;
            case Get_ExteriorTemperature2:
                Prm.floatExteriorTemperature = float(currentValue) / 100;
                Prm.ExteriorTemperature = Prm.baseExteriorTemperature + Prm.floatExteriorTemperature;
                break;

            case Get_ExteriorHumidity1:
                Prm.baseExteriorHumidity = currentValue;
                Prm.ExteriorHumidity = Prm.baseExteriorHumidity + Prm.floatExteriorHumidity;
                break;
            case Get_ExteriorHumidity2:
                Prm.floatExteriorHumidity = float(currentValue) / 100;
                Prm.ExteriorHumidity = Prm.baseExteriorHumidity + Prm.floatExteriorHumidity;
                break;

            case Get_ExteriorPressure1:
                Prm.ExteriorPressure = currentValue;
                break;
            case Get_ExteriorPressure2:
                Prm.ExteriorPressure += float(currentValue) / 100;
                break;
        }
        currentCommand = No_Command;
        currentValue = NO_VALUE;
    }/*
    else {
        switch (currentCommand) {
            case Get_Mode:
                break;
        }
    }*/
}

void Remote_SetCommand(Commands command)
{
    /*
    Serial.print(GotCommand);
    Serial.println(command);*/

    currentCommand = command;
    ProcessCommandValue();
}

void Remote_SetValue(byte value)
{
    /*
    Serial.print(GotValue);
    Serial.println(value);*/

    currentValue = value;
    ProcessCommandValue();
}
