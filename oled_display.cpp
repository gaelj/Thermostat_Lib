#include "oled_display.h"
#include <ZUNO_OLED_I2C.h>
#include <ZUNO_OLED_FONT_NUMB16.h>
#include "icons.h"
#include "timer.h"
#include "settings.h"


static OLED SCREEN;
static TimerClass MODE_BLINK_TIMER(OLED_BLINK_PERIOD);

static StringBuilderClass BLOCK;
static StringConverterClass CONV;

bool modeBlinkState;
byte lastBoilerState;
ThermostatMode lastMode;
float previousValues[PARAMETER_COUNT];
float* currentValuePointers[PARAMETER_COUNT] = {
    &SensorTemperature,
    &SensorHumidity,
    &Prm.ExteriorTemperature,
    &Prm.ExteriorHumidity,
    &Prm.ExteriorPressure,

    &PIDREG.lastInput,
    &PIDREG.lastSetpoint,
    &PIDREG.lastOutput,
    &PIDREG.outputSum,
    &PIDREG.error,
    &PIDREG.dInput,
    &PID_TIMER.Progress,
    &PID_TIMER.Duration,

    &BOILER_ON_TIMER.Progress,
    &BOILER_ON_TIMER.Duration,
    &Prm.TempDelta
};
byte currentPage = OLED_PAGE_COUNT;
bool forceRedraw;

bool ValuesOnCurrentPageHaveChanged();
void AppendLine(char* text, float value, char* unit);
void AppendEmptyLine(unsigned int startOfLineLength);

float prog = -1.0f;

static byte paramStartByPage[OLED_PAGE_COUNT + 1] = { 0, 5, 13, PARAMETER_COUNT };

static char* oledStrings[PARAMETER_COUNT] = {
    "Inside tmp",
    "Inside hum",
    "Outside tmp",
    "Outside hum",
    "Barometer",

    "PID lst inp",
    "PID lst sp",
    "PID lst out",
    "PID out sum",
    "PID err",
    "PID dInp",
    "PID prg",
    "PID dur",

    "Boiler prg",
    "Boiler dur",
    "Inside delta",
};

static char* unitStrings[] = {
    "",
    "%",
    "C",
    "mn"
};

enum Units {
    UnitNone,
    UnitPercentage,
    UnitCelcius,
    UnitMinutes
};

static Units UnitsPerString[PARAMETER_COUNT] = {
    UnitCelcius,
    UnitPercentage,
    UnitCelcius,
    UnitPercentage,
    UnitNone,

    UnitCelcius,
    UnitCelcius,
    UnitNone,
    UnitNone,
    UnitCelcius,
    UnitCelcius,
    UnitPercentage,
    UnitMinutes,

    UnitPercentage,
    UnitMinutes,
    UnitCelcius
};

static char* LoadingString = "Loading";

void OledDisplay_Init()
{
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
void OledDisplay_ShowNextPage()
{
    if (currentPage != OLED_PAGE_COUNT) {
        currentPage = (currentPage + 1) % OLED_PAGE_COUNT;
    }
    forceRedraw = true;
}

/**
* @brief Draw the screen
*
*/
void OledDisplay_DrawDisplay()
{
    bool redraw = ValuesOnCurrentPageHaveChanged();
    redraw = redraw || forceRedraw;
    if (redraw) {
        byte i = 0;
        BLOCK.Init();
        if (currentPage == OLED_PAGE_COUNT) {
            prog = (float(int(currentCommand) * 100)) / ZWAVE_MSG_COUNT;
            for (i = 0; i < 2; i++)
                AppendEmptyLine(0);
            AppendLine(LoadingString, prog, unitStrings[UnitPercentage]);
            
            if (currentCommand == ZWAVE_MSG_COUNT)
                currentPage = 0;
        }
        else {
            for (i = paramStartByPage[currentPage]; i < paramStartByPage[currentPage + 1]; i++) {
                AppendLine(oledStrings[i], *currentValuePointers[i], unitStrings[UnitsPerString[i]]);
            }
            for (i = paramStartByPage[currentPage + 1] - paramStartByPage[currentPage]; i < (currentPage == 0 ? OLED_TEXT_LINE_COUNT_P1 : OLED_TEXT_LINE_COUNT); i++) {
                AppendEmptyLine(0);
            }
        }

        SCREEN.gotoXY(0, 0);
        SCREEN.print(BLOCK.GetText());
    }

    // 1st page icons
    if (currentPage == 0) {

        bool modeChanged = Prm.CurrentThermostatMode != lastMode;
        bool boilerChanged = CurrentBoilerState != lastBoilerState;
        lastMode = Prm.CurrentThermostatMode;
        lastBoilerState = CurrentBoilerState;

        bool timerElapsed = false;
        if (MODE_BLINK_TIMER.IsElapsed() || modeChanged) {
            MODE_BLINK_TIMER.Start();
            modeBlinkState = modeChanged || !modeBlinkState;
            timerElapsed = true;
        }

        // blinking thermostat mode icon
        if (timerElapsed || modeChanged || redraw) {
            char* modeIcon = empty_icon;
            if (modeBlinkState) {
                switch (Prm.CurrentThermostatMode) {
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
            SCREEN.writeData(CurrentBoilerState ? flame_icon : empty_icon);
        }
    }
    forceRedraw = false;
}

void AppendLine(char* text, float value, char* unit)
{
    // Write definition string
    BLOCK.AppendString(text);
    
    // End-pad with spaces
    unsigned int len = strlen(text);
    //if (len < OLED_ROWHEADER_LEN)
    BLOCK.PadRight(" ", OLED_ROWHEADER_LEN - len);

    // Append value
    CONV.Init();
    CONV.fixPrint(int(value * 10), 1);
    char* conv = CONV.GetText();
    strcat(conv, unit);
    BLOCK.AppendString(conv);

    // End-pad with spaces
    len = OLED_ROWHEADER_LEN + strlen(conv);
    AppendEmptyLine(len);
}

void AppendEmptyLine(unsigned int startOfLineLength)
{
    BLOCK.PadRight(" ", OLED_TEXT_ROW_LEN - startOfLineLength);
}

/**
* @brief Set the OLED display power on or off
*
*/
void OledDisplay_SetPower(bool value)
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
bool ValuesOnCurrentPageHaveChanged()
{
    // Check for changes
    if (currentPage == OLED_PAGE_COUNT)
        return prog != ((float(int(currentCommand) * 100)) / ZWAVE_MSG_COUNT);

    bool ret = false;
    for (byte i = paramStartByPage[currentPage]; i < paramStartByPage[currentPage + 1]; i++) {
        if (previousValues[i] != *currentValuePointers[i]) {
            previousValues[i] = *currentValuePointers[i];
            ret = true;
        }
    }
    return ret;
}
