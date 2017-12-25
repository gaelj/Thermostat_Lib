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

static byte paramStartByPage[OLED_PAGE_COUNT + 1] = { 0, 5, 11, PARAMETER_COUNT };

OledDisplayClass::OledDisplayClass(SettingsClass* settings, SensorClass* sensor,
    BoilerClass* boiler, ThermostatClass* thermostat, PID* pid, LedControlClass* leds)
    : SETTINGS(settings), SENSOR(sensor), BOILER(boiler), THERM(thermostat), PIDREG(pid), LEDS(leds)
{
    currentPage = 0;
    modeBlinkState = false;
    forceRedraw = true;
    SCREEN.begin();
    SCREEN.setFont(SmallFont);
    SCREEN.clrscr();
    delay(OLED_WRITE_DELAY);
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
        delay(OLED_WRITE_DELAY);

        BLOCK.Init();
        for (byte i = paramStartByPage[currentPage]; i < paramStartByPage[currentPage + 1]; i++)
            AppendLine(oledStrings[i], currentValues[i]);

        SCREEN.gotoXY(0, 0);
        SCREEN.print(BLOCK.GetText());
    }

    // 1st page icons
    if (currentPage == 0) {

        bool modeChanged = THERM->CurrentThermostatMode != lastMode || BOILER->CurrentBoilerState != lastBoilerState;
        bool boilerChanged = THERM->CurrentThermostatMode != lastMode || BOILER->CurrentBoilerState != lastBoilerState;
        lastMode = THERM->CurrentThermostatMode;
        lastBoilerState = BOILER->CurrentBoilerState;

        bool timerElapsed = false;
        if (MODE_BLINK_TIMER.IsElapsed() || modeChanged) {
            MODE_BLINK_TIMER.Start();
            modeBlinkState = modeChanged || !modeBlinkState;
            timerElapsed = true;
        }

        // blinking thermostat mode icon
        if (timerElapsed || modeChanged) {
            char* modeIcon = empty_icon;
            if (modeBlinkState) {
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
        }

        // boiler state icon
        if (boilerChanged) {
            SCREEN.gotoXY(80, 5);
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
    // Store current values
    currentValues[0] = SENSOR->Temperature;
    currentValues[1] = LEDS->tempDelta;
    currentValues[2] = SENSOR->Humidity;
    currentValues[3] = THERM->ExteriorTemperature;
    currentValues[4] = -1;

    currentValues[5] = PIDREG->lastInput;
    currentValues[6] = PIDREG->lastOutput;
    currentValues[7] = PIDREG->outputSum;
    currentValues[8] = PIDREG->error;
    currentValues[9] = PIDREG->dInput;
    currentValues[11] = THERM->PID_TIMER->Progress;

    currentValues[10] = THERM->BOILER_TIMER->Progress;
    currentValues[12] = MillisToSeconds(THERM->BOILER_TIMER->DurationInMillis);

    // Check for changes
    bool ret = false;
    for (byte i = paramStartByPage[currentPage]; i < paramStartByPage[currentPage + 1]; i++)
        if (previousValues[i] != currentValues[i])
            ret = true;

    for (byte i = 0; i < PARAMETER_COUNT; i++)
        previousValues[i] = currentValues[i];

    return ret;
}
