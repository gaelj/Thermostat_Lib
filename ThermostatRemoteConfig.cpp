/*
 Name:		ThermostatRemoteConfig.cpp
 Created:	24/12/2017 22:00:55
 Author:	gael
 Editor:	http://www.visualmicro.com
*/

#include "ThermostatRemoteConfig.h"

char* GotCommand = "GC=";
char* GotValue = "GV=";

RemoteConfiguratorClass::RemoteConfiguratorClass()
{
    CurrentThermostatMode = Absent;
    baseExteriorTemperature = 10;
    floatExteriorTemperature = 0;
    ExteriorTemperature = 10;

    baseExteriorHumidity = 0;
    floatExteriorHumidity = 0;
    ExteriorHumidity = 0;

    currentCommand = No_Command;
    currentValue = NO_VALUE;
}

void RemoteConfiguratorClass::SetCommand(Commands command)
{
    /*
    Serial.print(GotCommand);
    Serial.println(command);*/

    currentCommand = command;
    ProcessCommandValue();
}

void RemoteConfiguratorClass::SetValue(byte value)
{
    /*
    Serial.print(GotValue);
    Serial.println(value);*/

    currentValue = value;
    ProcessCommandValue();
}

void RemoteConfiguratorClass::ProcessCommandValue()
{
    if (currentCommand != No_Command && currentValue != NO_VALUE) {
        /*
        Serial.print(GotCommand);
        Serial.print(currentCommand);
        Serial.print(GotValue);
        Serial.println(currentValue);*/

        switch (currentCommand) {
            case Get_Mode:
                CurrentThermostatMode = DecodeMode(currentValue);
                break;

            case Get_Radiator_Count:
                RadiatorCount = currentValue;
                break;
            case Get_ActiveRadiator:
                ActiveRadiator = currentValue;
                break;

            case Get_RadiatorSetpoint1:
                RadiatorSetpoint = currentValue;
                break;
            case Get_RadiatorSetpoint2:
                RadiatorSetpoint += float(currentValue) / 100;
                break;

            case Get_RadiatorTemperature1:
                RadiatorTemperature = currentValue;
                break;
            case Get_RadiatorTemperature2:
                RadiatorTemperature += float(currentValue) / 100;
                break;

            case Get_ExteriorTemperature1:
                baseExteriorTemperature = currentValue - 50;
                ExteriorTemperature = baseExteriorTemperature + floatExteriorTemperature;
                break;
            case Get_ExteriorTemperature2:
                floatExteriorTemperature = float(currentValue) / 100;
                ExteriorTemperature = baseExteriorTemperature + floatExteriorTemperature;
                break;

            case Get_ExteriorHumidity1:
                baseExteriorHumidity = currentValue;
                ExteriorHumidity = baseExteriorHumidity + floatExteriorHumidity;
                break;
            case Get_ExteriorHumidity2:
                floatExteriorHumidity = float(currentValue) / 100;
                ExteriorHumidity = baseExteriorHumidity + floatExteriorHumidity;
                break;

            case Get_ExteriorPressure1:
                ExteriorPressure = currentValue;
                break;
            case Get_ExteriorPressure2:
                ExteriorPressure += float(currentValue) / 100;
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
