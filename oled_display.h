#ifndef OLEDDISPLAY_H
#define OLEDDISPLAY_H

#include <Arduino.h>
#include <string.h>
#include <Print.h>

#include "string_builder.h"
#include "settings.h"
#include "sensor.h"
#include "boiler.h"
#include "thermo_control.h"
#include "enumerations.h"
#include "zwave_encoding.h"
#include "led_control.h"

#define OLED_PAGE_COUNT     3
#define OLED_WRITE_DELAY    5  // millis
#define OLED_BLINK_PERIOD   1000 // millis
#define OLED_ROWHEADER_LEN  15

class OledDisplayClass
{
public:
    OledDisplayClass(SettingsClass* settings, SensorClass* sensor,
        BoilerClass* boiler, ThermostatClass* thermostat, PID* pid,
        LedControlClass* leds);
    void DrawDisplay();
    void SetPower(bool value);
    void ShowNextPage();

private:
    SettingsClass* SETTINGS;
    SensorClass* SENSOR;
    BoilerClass* BOILER;
    ThermostatClass* THERM;
    LedControlClass* LEDS;
    PID* PIDREG;
    byte lastBoilerState;
    float lastTemp;
    ThermostatMode lastMode;
    byte currentPage;
    bool DisplayRedrawNeeded();
    void SaveLastValues();
    void AppendText(char* text, float value);
    void AppendLine(char* text, float value);
    void DrawCurrentPage();
    bool modeBlinkState;
    bool forceRedraw;
};

#endif // OLEDDISPLAY_H
