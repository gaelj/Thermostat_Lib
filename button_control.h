// button_control.h

#ifndef _BUTTON_CONTROL_h
#define _BUTTON_CONTROL_h

#include "Arduino.h"
#include "button.h"
#include "pinout.h"
#include "thermo_control.h"
#include "led_control.h"
#include "oled_display.h"
#include "ThermostatRemoteConfig.h"
#include "zwave_communication.h"


class ButtonControlClass
{
public:
    ButtonControlClass(ThermostatClass*, LedControlClass*, OledDisplayClass*, RemoteConfiguratorClass*, ZwaveCommunicationClass*);
    void ReadButtons();

protected:
    ThermostatClass* THERM;
    LedControlClass* LEDS;
    OledDisplayClass* DISPLAY;
    RemoteConfiguratorClass* REMOTE;
    ZwaveCommunicationClass* ZWAVE;
    bool button1Down, button2Down;
    bool power;
};

#endif
