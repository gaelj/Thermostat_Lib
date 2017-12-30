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
#include "radiator.h"

#define OLED_PAGE_COUNT     4
#define OLED_CLEAR_DELAY    5  // millis
#define OLED_BLINK_PERIOD   1000 // millis
#define OLED_ROWHEADER_LEN  15
#define PARAMETER_COUNT     20
#define ICONS_ROW           5
#define ICONS_COL1          20
#define ICONS_COL2          80

class OledDisplayClass
{
public:
    OledDisplayClass(PID*);
    void DrawDisplay();
    void SetPower(bool value);
    void ShowNextPage();

private:
    PID* PIDREG;

    bool modeBlinkState;
    byte lastBoilerState;
    ThermostatMode lastMode;
    float previousValues[PARAMETER_COUNT];
    float* currentValuePointers[PARAMETER_COUNT];
    byte currentPage;
    bool forceRedraw;

    bool ValuesOnCurrentPageHaveChanged();

    void AppendLine(char* text, float value);
};

#endif // OLEDDISPLAY_H
