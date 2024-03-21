#if !defined(DEVICE_H)
#define DEVICE_H

#include "controller.hpp"

// Struct for information regarding a GPIO register
struct gpio_register_t {
  int offset;
  int pins;
  int bit_width;
  int bit_fill;
  gpio_register_t() {}
  gpio_register_t(int _offset, int width): offset(_offset), bit_width(width) {
    pins = 32 / bit_width;
    bit_fill = 0x11111111 & ~(~1 << ((bit_width - 1) * 4));
  }
};

// LOW/HIGH constants
const int LOW = 0;
const int HIGH = 1;

/* Register memory offsets */
// 0x00 - Set the function of GPIO pins
const gpio_register_t GPFSEL(0, 3);
// 0x1c - Set a GPIO pin to `1`
const gpio_register_t GPSET(7, 1);
// 0x28 - Clear a GPIO pin to `0`
const gpio_register_t GPCLR(10, 1);
// 0x34 - Read the level of a GPIO pin
const gpio_register_t GPLEV(13, 1);
// 0x40 - Detect events on a GPIO pin
const gpio_register_t GPEDS(16, 1);
// 0x4c - Enable rising edge event detection on a GPIO pin
const gpio_register_t GPREN(19, 1);
// 0x58 - Enable falling edge event detection on a GPIO pin
const gpio_register_t GPFEN(22, 1);
// 0x64 - Enable high level event detection on a GPIO pin
const gpio_register_t GPHEN(25, 1);
// 0x70 - Enable low level event detection on a GPIO pin
const gpio_register_t GPLEN(28, 1);
// 0xe4 - Control the internal pull-up/down registers on a GPIO pin
const gpio_register_t GPIO_PUP_PDN_CNTROL_REG(57, 2);

// Pin modes
const int MODE_IN = 0;
const int MODE_OUT = 1;

class Device {
private:
  int pin;
  int mode;
  int active_high = HIGH;

protected:
  void set_register(gpio_register_t reg, int value);
  int read_register(gpio_register_t reg);

public:
  Device(int _pin, int _mode);
  Device(int _pin, int _mode, int _active_high);
  ~Device();

  int get_mode();
  int get_active_high();
  void set_active_high(int h);

  bool read();
};


#endif
