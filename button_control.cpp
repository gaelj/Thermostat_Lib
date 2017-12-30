#include "button_control.h"

static ButtonClass BUTTON1(PIN_BUTTON1);
static ButtonClass BUTTON2(PIN_BUTTON2);

bool button1Handled = true;
bool button2Handled = true;

ButtonActions ReadButtons()
{
    ButtonStateChange Event1 = BUTTON1.ReadButton();
    ButtonStateChange Event2 = BUTTON2.ReadButton();

    if (Event1 == OnPressed)
        button1Handled = false;

    if (Event2 == OnPressed)
        button2Handled = false;
    
    if (!button1Handled && !button2Handled) {
        button1Handled = true;
        button2Handled = true;
        return Button12;
    }

    if (Event1 == OnReleased && !button1Handled) {
        button1Handled = true;
        return Button1;
    }

    if (Event2 == OnReleased && !button2Handled) {
        button2Handled = true;
        return Button2;
    }

    return NoButtonAction;
}
