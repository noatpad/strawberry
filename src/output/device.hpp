#if !defined(OUTPUT_DEVICE_H)
#define OUTPUT_DEVICE_H

#include "../device.hpp"
#include <chrono>
#include <thread>

using milliseconds = chrono::duration<long double, std::milli>;

class OutputDevice: public Device {
public:
  OutputDevice(int pin);
  OutputDevice(int pin, int value);
  OutputDevice(int pin, int value, int active_high);
  ~OutputDevice();

  void write(int level);
  void off();
  void on();
  void toggle();
};

#endif // OUTPUT_DEVICE_H
