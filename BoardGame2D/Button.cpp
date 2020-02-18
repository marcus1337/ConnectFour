#include "Button.h"


Button::Button() {
    activated = true;
    selected = pressed = wasClicked = false;
    forcePress = false;
    hoverOn = true;
    rect.h = rect.w = 50;
}
