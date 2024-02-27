#include "device.hpp"

OutputDevice::OutputDevice(int pin): Device(pin, MODE_OUT) {}

OutputDevice::OutputDevice(int pin, int value): OutputDevice(pin, value, HIGH) {}
OutputDevice::OutputDevice(int pin, int value, int active_high): Device(pin, MODE_OUT, active_high) {
  write(value);
}

OutputDevice::~OutputDevice() {}

void OutputDevice::off() { write(LOW); }
void OutputDevice::on() { write(HIGH); }
void OutputDevice::toggle() { write(read() == HIGH ? LOW : HIGH); }
