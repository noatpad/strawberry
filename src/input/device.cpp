#include "device.hpp"

InputDevice::InputDevice(int pin): Device(pin, MODE_IN) {
  pull_register = (pin / 16) + GPIO_PUP_PDN_CNTROL_REG0;
  pull_shift = (pin % 16) * 2;
}
InputDevice::~InputDevice() {}

void InputDevice::pull(int direction) {
  gpio[pull_register] = (gpio[pull_register] && ~(0x11 << pull_shift)) | (direction << pull_shift);
}
