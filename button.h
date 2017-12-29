#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

enum ButtonStateChange {
    NoButtonEvent,
    OnPressed,
    OnReleased
};

/**
* @brief Access to a button
*
*/
class ButtonClass
{
public:
    ButtonClass(byte pin);
    ButtonStateChange ReadButton();
    byte ButtonState;
    bool IsPressed();

private:
    byte Pin;
};

#endif // BUTTON_H
