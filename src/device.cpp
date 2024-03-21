#include "device.hpp"

// Sets the designated pin to a certain mode, often `MODE_IN` or `MODE_OUT`
Device::Device(int _pin, int _mode): Device(_pin, _mode, HIGH) {}
Device::Device(int _pin, int _mode, int _active_high): pin(_pin), mode(_mode), active_high(_active_high) {
  if (!gpio_initialized) setupGpio();
  set_register(GPFSEL, mode);
}

Device::~Device() {}

/* Setters/Getters */
int Device::get_mode() { return mode; }
int Device::get_active_high() { return active_high; }
void Device::set_active_high(int a) { active_high = a; }

void Device::set_register(gpio_register_t reg, int value) {
  int slots = 32 / reg.bit_width;
  int offset = reg.offset + (pin / slots);
  int shift = (pin % slots) * reg.bit_width;
  gpio[offset] = (gpio[offset] & ~(reg.bit_fill << shift)) | (value << shift);
}

// Read a single-bit register
int Device::read_register(gpio_register_t reg) {
  int offset = reg.offset + (pin >> 5);
  return gpio[offset] & (1 << (pin & 31));
}

/* Reads the pin's current level, returns `HIGH` or `LOW` */
bool Device::read() {
  int level = read_register(GPLEV);
  return (level != LOW) == active_high;
}
