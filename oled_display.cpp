#include "oled_display.h"
#include <ZUNO_OLED_I2C.h>
#include <ZUNO_OLED_FONT_NUMB16.h>
#include "icons.h"
#include "oled_strings.h"
#include "timer.h"
#include "settings.h"


OLED SCREEN;
static TimerClass MODE_BLINK_TIMER(OLED_BLINK_PERIOD);
//static TimerClass PAGE_TIMER(OLED_PAGE_PERIOD);

static StringBuilderClass BLOCK;
static StringConverterClass CONV;

static byte paramStartByPage[OLED_PAGE_COUNT + 1] = { 0, 5, 12, PARAMETER_COUNT };

OledDisplayClass::OledDisplayClass(SettingsClass* settings, SensorClass* sensor,
    BoilerClass* boiler, ThermostatClass* thermostat, PID* pid, LedControlClass* leds, RemoteConfiguratorClass* remote)
    : SETTINGS(settings), SENSOR(sensor), BOILER(boiler), THERM(thermostat), PIDREG(pid), LEDS(leds), REMOTE(remote)
{
    currentValuePointers[0] = &SENSOR->Temperature;
    currentValuePointers[1] = &LEDS->tempDelta;
    currentValuePointers[2] = &SENSOR->Humidity;
    currentValuePointers[3] = &REMOTE->ExteriorTemperature;
    currentValuePointers[4] = &REMOTE->ExteriorHumidity;
    currentValuePointers[5] = &PIDREG->lastInput;
    currentValuePointers[6] = &PIDREG->lastOutput;
    currentValuePointers[7] = &PIDREG->outputSum;
    currentValuePointers[8] = &PIDREG->error;
    currentValuePointers[9] = &PIDREG->dInput;
    currentValuePointers[10] = &THERM->PID_TIMER->Progress;
    currentValuePointers[11] = &THERM->PID_TIMER->Duration;
    currentValuePointers[12] = &THERM->BOILER_ON_TIMER->Progress;
    currentValuePointers[13] = &THERM->BOILER_ON_TIMER->Duration;

    currentPage = 0;
    modeBlinkState = false;
    forceRedraw = true;
    SCREEN.begin();
    SCREEN.setFont(SmallFont);
    SCREEN.clrscr();
    delay(OLED_CLEAR_DELAY);
}

/**
* @brief Display the next page on the display
*
*/
void OledDisplayClass::ShowNextPage()
{
    currentPage = (currentPage + 1) % OLED_PAGE_COUNT;
    forceRedraw = true;
}

/**
* @brief Draw the screen
*
*/
void OledDisplayClass::DrawDisplay()
{
    /*bool timerElapsed = false;
    if (PAGE_TIMER.IsElapsed()) {
        PAGE_TIMER.Start();
        currentPage = (currentPage + 1) % OLED_PAGE_COUNT;
        timerElapsed = true;
    }*/
    bool redraw = ValuesOnCurrentPageHaveChanged();
    redraw = redraw || forceRedraw/*|| timerElapsed*/;
    if (redraw) {
        SCREEN.clrscr();
        delay(OLED_CLEAR_DELAY);

        BLOCK.Init();
        for (byte i = paramStartByPage[currentPage]; i < paramStartByPage[currentPage + 1]; i++)
            AppendLine(oledStrings[i], *currentValuePointers[i]);

        SCREEN.gotoXY(0, 0);
        SCREEN.print(BLOCK.GetText());
    }

    // 1st page icons
    if (currentPage == 0) {

        bool modeChanged = REMOTE->CurrentThermostatMode != lastMode;
        bool boilerChanged = BOILER->CurrentBoilerState != lastBoilerState;
        lastMode = REMOTE->CurrentThermostatMode;
        lastBoilerState = BOILER->CurrentBoilerState;

        bool timerElapsed = false;
        if (MODE_BLINK_TIMER.IsElapsed() || modeChanged) {
            MODE_BLINK_TIMER.Start(0);
            modeBlinkState = modeChanged || !modeBlinkState;
            timerElapsed = true;
        }

        // blinking thermostat mode icon
        if (timerElapsed || modeChanged || redraw) {
            char* modeIcon = empty_icon;
            if (modeBlinkState) {
                switch (REMOTE->CurrentThermostatMode) {
                    case Frost: modeIcon = snow_icon; break;
                    case Absent: modeIcon = absent_icon; break;
                    case Night: modeIcon = moon_icon; break;
                    case Day: modeIcon = sun_icon; break;
                    case Warm: modeIcon = hot_icon; break;
                }
            }
            SCREEN.gotoXY(ICONS_COL1, ICONS_ROW);
            SCREEN.writeData(modeIcon);
        }

        // boiler state icon
        if (boilerChanged || redraw) {
            SCREEN.gotoXY(ICONS_COL2, ICONS_ROW);
            SCREEN.writeData(BOILER->CurrentBoilerState ? flame_icon : empty_icon);
        }
    }
    forceRedraw = false;
}

void OledDisplayClass::AppendLine(char* text, float value)
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

    // Append newline
    BLOCK.AppendString("\n");
}

/**
* @brief Set the OLED display power on or off
*
*/
void OledDisplayClass::SetPower(bool value)
{
    if (value) {
        SCREEN.on();
        forceRedraw = true;
    }
    else
        SCREEN.off();
}

/**
* @brief Should the display be redrawn, due to source data update. Reads the temperature sensor
*
*/
bool OledDisplayClass::ValuesOnCurrentPageHaveChanged()
{
    // Check for changes
    bool ret = false;
    for (byte i = paramStartByPage[currentPage]; i < paramStartByPage[currentPage + 1]; i++) {
        if (previousValues[i] != *currentValuePointers[i]) {
            previousValues[i] = *currentValuePointers[i];
            ret = true;
        }
    }
    return ret;
}
