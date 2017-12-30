/*
 Name:		ThermostatRemoteConfig.cpp
 Created:	24/12/2017 22:00:55
 Author:	gael
 Editor:	http://www.visualmicro.com
*/

#include "ThermostatRemoteConfig.h"

Commands currentCommand = No_Command;
byte currentValue = NO_VALUE;
TimerClass TIMEOUT_TIMER(TIMEOUT_DELAY);

void Remote_InitParameters()
{
    Prm.CurrentThermostatMode = Absent;
    Prm.baseExteriorTemperature = 50;
    Prm.floatExteriorTemperature = 0;

    Prm.baseExteriorHumidity = 0;
    Prm.floatExteriorHumidity = 0;

    for (byte i = 0; i < 6; i++) {
        Radiators[i].baseSetPoint = 50;
        Radiators[i].floatSetPoint = 0;
    }
}

byte GetRadId(byte commandBase)
{
    return (currentCommand - commandBase) / 4;
}

void ProcessCommandValue()
{
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
                Radiators[radiatorId].baseSetPoint = currentValue;
                break;
            case Get_Radiator0Setpoint2:
            case Get_Radiator1Setpoint2:
            case Get_Radiator2Setpoint2:
            case Get_Radiator3Setpoint2:
            case Get_Radiator4Setpoint2:
            case Get_Radiator5Setpoint2:
                radiatorId = GetRadId(Get_Radiator0Setpoint2);
                Radiators[radiatorId].floatSetPoint = currentValue;
                break;

            case Get_Radiator0Temperature1:
            case Get_Radiator1Temperature1:
            case Get_Radiator2Temperature1:
            case Get_Radiator3Temperature1:
            case Get_Radiator4Temperature1:
            case Get_Radiator5Temperature1:
                radiatorId = GetRadId(Get_Radiator0Temperature1);
                Radiators[radiatorId].baseTemperature = currentValue;
                break;
            case Get_Radiator0Temperature2:
            case Get_Radiator1Temperature2:
            case Get_Radiator2Temperature2:
            case Get_Radiator3Temperature2:
            case Get_Radiator4Temperature2:
            case Get_Radiator5Temperature2:
                radiatorId = GetRadId(Get_Radiator0Temperature2);
                Radiators[radiatorId].floatTemperature = currentValue;
                break;

            case Get_ExteriorTemperature1:
                Prm.baseExteriorTemperature = currentValue;
                break;
            case Get_ExteriorTemperature2:
                Prm.floatExteriorTemperature = currentValue;
                break;

            case Get_ExteriorHumidity1:
                Prm.baseExteriorHumidity = currentValue;
                break;
            case Get_ExteriorHumidity2:
                Prm.floatExteriorHumidity = currentValue;
                break;

            case Get_ExteriorPressure1:
                Prm.ExteriorPressure = currentValue;
                break;
            case Get_ExteriorPressure2:
                Prm.ExteriorPressure += float(currentValue) / 100;
                break;
        }

        if (radiatorId != 0xFF) {
            Radiators[radiatorId].SetPoint = CalculateTemperature(
                Radiators[radiatorId].baseSetPoint,
                Radiators[radiatorId].floatSetPoint);

            Radiators[radiatorId].Temperature = CalculateTemperature(
                Radiators[radiatorId].baseTemperature,
                Radiators[radiatorId].floatTemperature);
        }

        Prm.ExteriorTemperature = CalculateTemperature(
            Prm.baseExteriorTemperature,
            Prm.floatExteriorTemperature);

        Prm.ExteriorHumidity = float(Prm.baseExteriorHumidity) + (float(Prm.floatExteriorHumidity) / 100.0f);

        Serial.print("*** Cmd processed: ");
        Serial.print(currentCommand);
        Serial.print(" ");
        Serial.println(currentValue);

        currentCommand = No_Command;
        currentValue = NO_VALUE;
        TIMEOUT_TIMER.IsActive = false;
    }
    else {
        TIMEOUT_TIMER.Start();
    }
}

void Remote_SetCommand(Commands command)
{
    Serial.print(millis());
    Serial.print(" C=");
    Serial.println(command);
    
    if (TIMEOUT_TIMER.IsActive && TIMEOUT_TIMER.IsElapsed()) {
        currentValue = NO_VALUE;
    }

    currentCommand = command;
    ProcessCommandValue();
}

void Remote_SetValue(byte value)
{
    Serial.print(millis());
    Serial.print(" V=");
    Serial.println(value);

    if (TIMEOUT_TIMER.IsActive && TIMEOUT_TIMER.IsElapsed()) {
        currentCommand = No_Command;
    }

    currentValue = value;
    ProcessCommandValue();
}
