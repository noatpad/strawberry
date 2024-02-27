#if !defined(INPUT_DEVICE_H)
#define INPUT_DEVICE_H

#include "../device.hpp"

class InputDevice: public Device {
private:
  int pull_up_down;
  int pull_register;
  int pull_shift;

public:
  InputDevice(int pin);
  ~InputDevice();

  void pull(int direction);
};

#endif // INPUT_DEVICE_H
