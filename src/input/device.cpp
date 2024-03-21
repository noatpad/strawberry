#include "device.hpp"

InputDevice::InputDevice(int pin): InputDevice(pin, PULL_NONE) {}
InputDevice::InputDevice(int pin, int pull_direction): Device(pin, MODE_IN) {
  if (pull_direction) pull(pull_direction);
}
InputDevice::~InputDevice() {}

void InputDevice::pull(int direction) {
  set_register(GPIO_PUP_PDN_CNTROL_REG0, 2, direction);
  set_active_high(direction == PULL_UP ? LOW : HIGH);
}

void InputDevice::wait_until_active() {

}
