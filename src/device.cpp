#include "device.hpp"

Device::Device(int _pin, int _mode): Device(_pin, _mode, HIGH) {}
Device::Device(int _pin, int _mode, int _active_high): pin(_pin), mode(_mode), active_high(_active_high) {
  if (!gpio_initialized) setupGpio();

  // Sets the designated pin to a certain mode, often `MODE_IN` or `MODE_OUT`
  set_register(GPFSEL0, 3, mode);
  // int reg = pin / 10;
  // int shift = (pin % 10) * 3;
  // gpio[reg] = (gpio[reg] & ~(0x111 << shift)) | (mode << shift);

  // rwBank = pin >> 5;
  // rwBit = 1 << (pin & 31);
}

Device::~Device() {}

/* Setters/Getters */
int Device::get_mode() { return mode; }
int Device::get_active_high() { return active_high; }
void Device::set_active_high(int a) { active_high = a; }

void Device::set_register(int reg, int bit_width, int value) {
  int slots = 32 / bit_width;
  int offset = reg + (pin / slots);
  int shift = (pin % slots) * bit_width;
  // int fill = pow(2, bit_width) - 1;
  int fill = ~(0 << (bit_width - 1));
  gpio[offset] = (gpio[offset] & ~(fill << shift)) | (value << shift);
}

int Device::read_register(int reg, int bit_width) {
  int offset = reg + (pin * bit_width / 32);
  int fill = pow(2, bit_width) - 1;
  return gpio[offset] & fill;
}

/* Reads the pin's current level, returns `HIGH` or `LOW` */
bool Device::read() {
  // int level = gpio[GPLEV0 + rwBank] & rwBit;
  int level = read_register(GPLEV0, 1);
  return (level != LOW) == active_high;
}
