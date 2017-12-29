#include "button_control.h"

static ButtonClass BUTTON1(PIN_BUTTON1);
static ButtonClass BUTTON2(PIN_BUTTON2);

bool button1Unhandled = false;
bool button2Unhandled = false;

ButtonActions ReadButtons()
{
    ButtonStateChange Event1 = BUTTON1.ReadButton();
    ButtonStateChange Event2 = BUTTON2.ReadButton();

    if (Event1 == OnPressed)
        button1Unhandled = true;
    if (Event2 == OnPressed)
        button2Unhandled = true;
    
    if (button1Unhandled && button2Unhandled) {
        button1Unhandled = false;
        button2Unhandled = false;
        return Button12;
    }

    if (Event1 == OnReleased && button1Unhandled) {
        button1Unhandled = false;
        return Button1;
    }
    if (Event2 == OnReleased && button2Unhandled) {
        button2Unhandled = false;
        return Button2;
    }
}
