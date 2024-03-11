#include "device.hpp"

OutputDevice::OutputDevice(int pin): Device(pin, MODE_OUT) {}

OutputDevice::OutputDevice(int pin, int value): OutputDevice(pin, value, HIGH) {}
OutputDevice::OutputDevice(int pin, int value, int active_high): Device(pin, MODE_OUT, active_high) {
  write(value);
}

OutputDevice::~OutputDevice() {}

/* Sets the pin's level to `HIGH` or `LOW` */
void OutputDevice::write(int level) {
  if (level == read()) return;
  int reg = (level == HIGH ? GPSET0 : GPCLR0);
  gpio[reg + rwBank] = rwBit;
}

void OutputDevice::off() { write(LOW); }
void OutputDevice::on() { write(HIGH); }
void OutputDevice::toggle() { write(read() == HIGH ? LOW : HIGH); }
