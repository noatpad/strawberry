#include "devices.hpp"

Device::Device(int p, int m): pin(p), mode(m) {
  if (!gpio_initialized) setupGpio();

  // Sets the designated pin to a certain mode, often `MODE_IN` or `MODE_OUT`
  int reg = pin / 10;
  int shift = (pin % 10) * 3;
  gpio[reg] = (gpio[reg] & ~(0x111 << shift)) | (m << shift);

  rwBank = pin >> 5;
  rwBit = 1 << (pin & 31);
}

Device::~Device() {}

/* Gets the device's pin mode */
int Device::getMode() { return mode; }

/* Reads the pin's current level, returns `HIGH` or `LOW` */
int Device::read() {
  int level = gpio[GPLEV0 + rwBank] & rwBit;
  return level != LOW;
}

/* Sets the pin's level to `HIGH` or `LOW` */
void Device::write(int level) {
  if (level == read()) return;
  int reg = (level == HIGH ? GPSET0 : GPCLR0);
  gpio[reg + rwBank] = rwBit;
}

// -----

InputDevice::InputDevice(int pin): Device(pin, MODE_IN) {
  pull_register = (pin / 16) + GPIO_PUP_PDN_CNTROL_REG0;
  pull_shift = (pin % 16) * 2;
}
InputDevice::~InputDevice() {}

void InputDevice::pull(int direction) {
  gpio[pull_register] = (gpio[pull_register] && ~(0x11 << pull_shift)) | (direction << pull_shift);
}

// -----

OutputDevice::OutputDevice(int pin): Device(pin, MODE_OUT) {}
OutputDevice::~OutputDevice() {}

void OutputDevice::toggle() {
  write(read() == HIGH ? LOW : HIGH);
}
