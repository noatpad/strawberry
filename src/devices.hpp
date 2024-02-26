#ifndef DEVICES_H
#define DEVICES_H

#include "strawberry.hpp"

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

protected:
  int rwBank;
  int rwBit;

public:
  Device(int p, int m);
  ~Device();

  int getMode();
  int read();
  void write(int level);
};

// -----

class InputDevice: public Device {
private:
  int pull_up_down;
  int pull_register;
  int pull_shift;

public:
  InputDevice(int pin);
  ~InputDevice();

  void pull(int direction);
};

// -----

class OutputDevice: public Device {
public:
  OutputDevice(int pin);
  ~OutputDevice();

  void toggle();
};

#endif
