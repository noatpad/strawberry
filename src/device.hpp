#if !defined(DEVICE_H)
#define DEVICE_H

#include "controller.hpp"

// LOW/HIGH constants
const int LOW = 0;
const int HIGH = 1;

// Register memory offsets
const int GPSET0 = 7;                       // 0x1c
const int GPCLR0 = 10;                      // 0x28
const int GPLEV0 = 13;                      // 0x34
const int GPIO_PUP_PDN_CNTROL_REG0 = 57;    // 0xe4

// Pin modes
const int MODE_IN = 0;
const int MODE_OUT = 1;
// const int MODE_ALT0 = 2;
// const int MODE_ALT1 = 3;
// const int MODE_ALT2 = 4;
// const int MODE_ALT3 = 5;
// const int MODE_ALT4 = 6;
// const int MODE_ALT5 = 7;

// Pull up/down options
const int PULL_NONE = 0;
const int PULL_UP = 1;
const int PULL_DOWN = 2;

class Device {
private:
  int pin;
  int mode;
  int active_high = HIGH;

protected:
  int rwBank;
  int rwBit;

public:
  Device(int _pin, int _mode);
  Device(int _pin, int _mode, int _active_high);
  ~Device();

  int getMode();
  bool read();
  void write(int level);
};


#endif
