#if !defined(OUTPUT_DEVICE_H)
#define OUTPUT_DEVICE_H

#include "../device.hpp"

class OutputDevice: public Device {
public:
  OutputDevice(int pin);
  ~OutputDevice();

  void toggle();
};

#endif // OUTPUT_DEVICE_H
