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

// Registers
const int GPEDS0 = 16;                      // 0x10
const int GPREN0 = 19;                      // 0x13
const int GPFEN0 = 22;                      // 0x16
// const int GPHEN0 = 25;                   // 0x19
// const int GPLEN0 = 28;                   // 0x1c
const int GPIO_PUP_PDN_CNTROL_REG0 = 57;    // 0xe4

class InputDevice: public Device {
public:
  InputDevice(int pin);
  InputDevice(int pin, int pull_direction);
  ~InputDevice();

  void pull(int direction);
  void wait_until_active();
};

#endif // INPUT_DEVICE_H
