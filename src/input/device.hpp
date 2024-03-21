#if !defined(INPUT_DEVICE_H)
#define INPUT_DEVICE_H

#include "../device.hpp"

// Pull up/down options
const int PULL_NONE = 0;
const int PULL_UP = 1;
const int PULL_DOWN = 2;

const int WAIT_FOR_NONE = 0;
const int WAIT_FOR_RISE = 1;
const int WAIT_FOR_FALL = 2;
const int WAIT_FOR_BOTH = 3;

class InputDevice: public Device {
public:
  InputDevice(int pin);
  InputDevice(int pin, int pull_direction);
  ~InputDevice();

  void pull(int direction);
  void wait_until_active();
};

#endif // INPUT_DEVICE_H
