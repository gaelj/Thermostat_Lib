#include "button_control.h"

static ButtonClass BUTTON1(PIN_BUTTON1);
static ButtonClass BUTTON2(PIN_BUTTON2);

ButtonControlClass::ButtonControlClass(ThermostatClass* thermostat, LedControlClass* leds, OledDisplayClass* display, RemoteConfiguratorClass* remote, ZwaveCommunicationClass* zwave):
    THERM(thermostat), LEDS(leds), DISPLAY(display), REMOTE(remote), ZWAVE(zwave)
{
    button1Down = false;
    button2Down = false;
    power = true;
}

void ButtonControlClass::ReadButtons()
{
    ButtonStateChange Event1 = BUTTON1.ReadButton();
    ButtonStateChange Event2 = BUTTON2.ReadButton();

    if (Event1 == OnPressed)
        button1Down = true;
    if (Event2 == OnPressed)
        button2Down = true;

    if ((button1Down && button2Down) || (!power && (button1Down || button2Down))) {
        // toggle power
        power = !power;
        LEDS->SetPower(power);
        DISPLAY->SetPower(power);
        button1Down = false;
        button2Down = false;
    }
    else if (Event1 == OnReleased && button1Down) {
        ThermostatMode newMode = ThermostatMode((byte(REMOTE->CurrentThermostatMode) + 1) % THERMOSTAT_MODE_COUNT);
        REMOTE->CurrentThermostatMode = newMode;

        ZWAVE->SendCommandValue(Set_Mode, EncodeMode(REMOTE->CurrentThermostatMode));

        button1Down = false;
    }
    else if (Event2 == OnReleased && button2Down) {
        DISPLAY->ShowNextPage();
        button2Down = false;
    }
}
