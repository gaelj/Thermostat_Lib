#include "oled_display.h"
#include <ZUNO_OLED_I2C.h>
#include <ZUNO_OLED_FONT_NUMB16.h>
#include "icons.h"
#include "oled_strings.h"
#include "timer.h"
#include "settings.h"


OLED SCREEN;
TimerClass MODE_BLINK_TIMER(OLED_BLINK_PERIOD);
//TimerClass PAGE_TIMER(OLED_PAGE_PERIOD);

StringBuilderClass BLOCK;
StringConverterClass CONV;

OledDisplayClass::OledDisplayClass(SettingsClass* settings, SensorClass* sensor,
    BoilerClass* boiler, ThermostatClass* thermostat, PID* pid, LedControlClass* leds)
    : SETTINGS(settings), SENSOR(sensor), BOILER(boiler), THERM(thermostat), PIDREG(pid), LEDS(leds)
{
    currentPage = 0;
    modeBlinkState = false;
    SaveLastValues();
    SCREEN.begin();
    delay(OLED_WRITE_DELAY);
    SCREEN.clrscr();
    delay(OLED_WRITE_DELAY);
    SCREEN.setFont(SmallFont);
    delay(OLED_WRITE_DELAY);
}

/**
* @brief Display the next page on the display
*
*/
void OledDisplayClass::ShowNextPage()
{
    currentPage = (currentPage + 1) % OLED_PAGE_COUNT;
    MODE_BLINK_TIMER.IsActive = false;
    DrawDisplay(true);
}

/**
* @brief Draw the screen
*
*/
void OledDisplayClass::DrawDisplay(bool force)
{
    /*bool timerElapsed = false;
    if (PAGE_TIMER.IsElapsed()) {
        PAGE_TIMER.Start();
        currentPage = (currentPage + 1) % OLED_PAGE_COUNT;
        timerElapsed = true;
    }*/
    bool redraw = DisplayRedrawNeeded() || force/*|| timerElapsed*/;
    if (redraw) {
        SCREEN.clrscr();
        delay(OLED_WRITE_DELAY);
        DrawCurrentPage();
    }

    // 1st page icons
    if (currentPage == 0) {
        char* modeIcon = empty_icon;
        bool timerElapsed = false;
        if (MODE_BLINK_TIMER.IsElapsed()) {
            MODE_BLINK_TIMER.Start();
            modeBlinkState = !modeBlinkState;
            timerElapsed = true;
        }

        if (timerElapsed || redraw) {
            // blinking thermostat mode icon
            if (modeBlinkState || force) {
                switch (THERM->CurrentThermostatMode) {
                case Frost: modeIcon = snow_icon; break;
                case Absent: modeIcon = absent_icon; break;
                case Night: modeIcon = moon_icon; break;
                case Day: modeIcon = sun_icon; break;
                case Warm: modeIcon = hot_icon; break;
                }
            }
            SCREEN.gotoXY(20, 5);
            SCREEN.writeData(modeIcon);
            delay(OLED_WRITE_DELAY);

            // boiler state icon
            if (BOILER->CurrentBoilerState) {
                SCREEN.gotoXY(80, 5);
                SCREEN.writeData(flame_icon);
                delay(OLED_WRITE_DELAY);
            }
        }
    }
}

/**
* @brief Draw page by id
*
*/
void OledDisplayClass::DrawCurrentPage()
{
    byte i = 0;
    float values[3];

    BLOCK.Init();

    switch (currentPage) {
        case 0:
            AppendLine(insideTemperature, SENSOR->Temperature);
            AppendLine(insideHumidity, SENSOR->Humidity);
            AppendLine(outsideTemperature, THERM->ExteriorTemperature);
            AppendText(insideTemperaturePrevious, LEDS->lastTemp);
            break;

        case 1:
            AppendLine(pidLastInput, PIDREG->lastInput);
            AppendLine(pidLastOutput, PIDREG->lastOutput);
            AppendLine(pidOutputSum, PIDREG->outputSum);
            AppendText(pidError, PIDREG->error);
            break;

        case 2:
            AppendLine(pidDInput, PIDREG->dInput);
            AppendLine(boilerTimerProgress, THERM->BOILER_TIMER->Progress);
            AppendLine(pidTimerProgress, THERM->PID_TIMER->Progress);
            float boilerDurationInSecs = (float(THERM->BOILER_TIMER->DurationInMillis) / 1000) / 60;
            AppendText(boilerTimerDuration, boilerDurationInSecs);
            break;
    }

    SCREEN.gotoXY(0, 0);
    SCREEN.print(BLOCK.GetText());
    Serial.println(BLOCK.GetText());
    delay(OLED_WRITE_DELAY);
}

void OledDisplayClass::AppendLine(char* text, float value)
{
    AppendText(text, value);
    // Append newline
    BLOCK.AppendString("\n");
}

void OledDisplayClass::AppendText(char* text, float value)
{
    // Write definition string
    BLOCK.AppendString(text);
    
    // End-pad with spaces
    unsigned int len = strlen(text);
    if (len < OLED_ROWHEADER_LEN)
        BLOCK.PadRight(" ", OLED_ROWHEADER_LEN - len);

    // Append value
    CONV.Init();
    CONV.fixPrint(int(value * 100), 2);
    char* conv = CONV.GetText();
    BLOCK.AppendString(conv);
}

/**
* @brief Set the OLED display power on or off
*
*/
void OledDisplayClass::SetPower(bool value)
{
    if (value) {
        SCREEN.on();
        DrawDisplay(true);
    }
    else
        SCREEN.off();
}

/**
* @brief Should the display be redrawn, due to source data update. Reads the temperature sensor
*
*/
bool OledDisplayClass::DisplayRedrawNeeded()
{
    // Refresh display if temperature has changed
    // Refresh display if thermostat mode has changed
    // Refresh display if boiler state has changed
    bool result = false;
    if (SENSOR->Temperature != lastTemp ||
        THERM->CurrentThermostatMode != lastMode ||
        BOILER->CurrentBoilerState != lastBoilerState) {
        SaveLastValues();
        result = true;
    }
    return result;
}

void OledDisplayClass::SaveLastValues()
{
    lastTemp = SENSOR->Temperature;
    lastMode = THERM->CurrentThermostatMode;
    lastBoilerState = BOILER->CurrentBoilerState;
}
