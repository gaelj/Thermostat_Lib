#ifndef OLEDDISPLAY_H
#define OLEDDISPLAY_H

#include <Arduino.h>
#include <string.h>
#include <Print.h>

#include "globals.h"
#include "string_builder.h"
#include "settings.h"
#include "sensor.h"
#include "boiler.h"
#include "thermo_control.h"
#include "enumerations.h"
#include "zwave_encoding.h"
#include "led_control.h"

#define OLED_PAGE_COUNT         3
#define OLED_TEXT_LINE_COUNT_P1 5
#define OLED_TEXT_LINE_COUNT    8
#define OLED_TEXT_ROW_LEN       21
#define OLED_CLEAR_DELAY        2    // millis
#define OLED_BLINK_PERIOD       1000 // millis
#define OLED_ROWHEADER_LEN      14
#define PARAMETER_COUNT         16
#define ICONS_ROW               5
#define ICONS_COL1              15
#define ICONS_COL2              50
#define ICONS_COL3              85

void OledDisplay_Init();
void OledDisplay_DrawDisplay();
void OledDisplay_SetPower(bool value);
void OledDisplay_ShowNextPage();

#endif // OLEDDISPLAY_H
