#include "device.hpp"

Device::Device(int _pin, int _mode): pin(_pin), mode(_mode) {
  if (!gpio_initialized) setupGpio();

  // Sets the designated pin to a certain mode, often `MODE_IN` or `MODE_OUT`
  int reg = pin / 10;
  int shift = (pin % 10) * 3;
  gpio[reg] = (gpio[reg] & ~(0x111 << shift)) | (mode << shift);

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
