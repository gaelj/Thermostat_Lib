#ifndef ZWAVE_COM_H
#define ZWAVE_COM_H

#include <Arduino.h>
#include <ZUNO_legacy_channels.h>
#include <ZUNO_channels.h>
#include <ZUNO_Definitions.h>
#include <ZUNO_OLED_I2C.h>
#include <ZUNO_OLED_FONT_NUMB16.h>
#include "globals.h"
#include "enumerations.h"
#include "zwave_encoding.h"
#include "ThermostatRemoteConfig.h"

// Defines the order of the Zwave channels
#define ZUNO_REPORT_ZTXCOMMAND     1
#define ZUNO_REPORT_ZTXVALUE       2
#define ZUNO_REPORT_ZRXCOMMAND     3
#define ZUNO_REPORT_ZRXVALUE       4
#define ZUNO_REPORT_TEMP           5
#define ZUNO_REPORT_HUMIDITY       6

void ReportTXCommandValue(byte, byte);
void ReportRXCommandValue(byte, byte);
void ReportTemperature();
void ReportHumidity();

#endif // ZWAVE_COM_H
