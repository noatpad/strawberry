#include "device.hpp"

Device::Device(int _pin, int _mode): Device(_pin, _mode, HIGH) {}
Device::Device(int _pin, int _mode, int _active_high): pin(_pin), mode(_mode), active_high(_active_high) {
  if (!gpio_initialized) setupGpio();

  // Sets the designated pin to a certain mode, often `MODE_IN` or `MODE_OUT`
  int reg = pin / 10;
  int shift = (pin % 10) * 3;
  gpio[reg] = (gpio[reg] & ~(0x111 << shift)) | (mode << shift);

  rwBank = pin >> 5;
  rwBit = 1 << (pin & 31);
}

Device::~Device() {}

/* Setters/Getters */
int Device::get_mode() { return mode; }
int Device::get_active_high() { return active_high; }
void Device::set_active_high(int a) { active_high = a; }

/* Reads the pin's current level, returns `HIGH` or `LOW` */
bool Device::read() {
  int level = gpio[GPLEV0 + rwBank] & rwBit;
  return (level != LOW) == active_high;
}
