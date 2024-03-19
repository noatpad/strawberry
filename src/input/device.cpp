#include "device.hpp"

InputDevice::InputDevice(int pin): InputDevice(pin, PULL_NONE) {}
InputDevice::InputDevice(int pin, int pull_direction): Device(pin, MODE_IN) {
  pull_register = (pin / 16) + GPIO_PUP_PDN_CNTROL_REG0;
  pull_shift = (pin % 16) * 2;
  // event_bank = pin >> 5;
  // event_bit = 1 << (pin & 31);
  if (pull_direction) pull(pull_direction);
}
InputDevice::~InputDevice() {}

void InputDevice::pull(int direction) {
  // gpio[pull_register] = (gpio[pull_register] && ~(0x11 << pull_shift)) | (direction << pull_shift);
  set_register(GPIO_PUP_PDN_CNTROL_REG0, 2, direction);
  set_active_high(direction == PULL_UP ? LOW : HIGH);
}

void InputDevice::wait_until_active() {

}
