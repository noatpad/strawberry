#include "button.hpp"

Button::Button(int pin): InputDevice(pin, PULL_UP) {}
Button::~Button() {}

bool Button::is_pressed() { return read(); }
