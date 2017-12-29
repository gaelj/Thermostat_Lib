// button_control.h

#ifndef _BUTTON_CONTROL_h
#define _BUTTON_CONTROL_h

#include "Arduino.h"
#include "globals.h"
#include "button.h"
#include "pinout.h"
#include "thermo_control.h"
#include "led_control.h"
#include "oled_display.h"
#include "ThermostatRemoteConfig.h"
#include "zwave_communication.h"

enum ButtonActions {
    NoButtonAction,
    Button1,
    Button2,
    Button12,
};

ButtonActions ReadButtons();

#endif
