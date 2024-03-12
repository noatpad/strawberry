#if !defined(LED_H)
#define LED_H

#include "device.hpp"

class LED: OutputDevice {
public:
  LED(int pin);
  LED(int pin, int value);
  LED(int pin, int value, int active_high);
  ~LED();

  void blink(double time);
  void blink(double on_time, double off_time);
  void blink(double time, int n);
  void blink(double on_time, double off_time, int n);
  // TODO: Add background blinking capability
};

#endif // LED_H
