#include "button.h"

ButtonClass::ButtonClass(byte pin)
{
    Pin = pin;
    ButtonState = HIGH;
    pinMode(Pin, INPUT);
}

ButtonStateChange ButtonClass::ReadButton()
{
    byte reading = digitalRead(Pin);
    if (ButtonState != reading) {
        ButtonState = reading;
        if (ButtonState == LOW)
            return OnPressed;
        return OnReleased;
    }
    return None;
}
