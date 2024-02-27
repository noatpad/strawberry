#if !defined(INPUT_DEVICE_H)
#define INPUT_DEVICE_H

#include "../device.hpp"

// Pull up/down options
const int PULL_NONE = 0;
const int PULL_UP = 1;
const int PULL_DOWN = 2;

const int GPIO_PUP_PDN_CNTROL_REG0 = 57;    // 0xe4

class InputDevice: public Device {
private:
  int pull_register;
  int pull_shift;

public:
  InputDevice(int pin);
  InputDevice(int pin, int pull_direction);
  ~InputDevice();

  void pull(int direction);
};

#endif // INPUT_DEVICE_H
