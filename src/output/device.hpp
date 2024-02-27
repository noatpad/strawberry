#if !defined(OUTPUT_DEVICE_H)
#define OUTPUT_DEVICE_H

#include "../device.hpp"

class OutputDevice: public Device {
private:
  bool flipped;

public:
  OutputDevice(int pin);
  OutputDevice(int pin, int value);
  OutputDevice(int pin, int value, int active_high);
  ~OutputDevice();

  void off();
  void on();
  void toggle();
};

#endif // OUTPUT_DEVICE_H
