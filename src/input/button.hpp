#if !defined(BUTTON_H)
#define BUTTON_H

#include "device.hpp"

class Button: InputDevice {
public:
  Button(int pin);
  ~Button();

  bool is_pressed();
};

#endif // BUTTON_H
