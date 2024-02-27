#include "device.hpp"

OutputDevice::OutputDevice(int pin): Device(pin, MODE_OUT) {}
OutputDevice::~OutputDevice() {}

void OutputDevice::toggle() {
  write(read() == HIGH ? LOW : HIGH);
}
