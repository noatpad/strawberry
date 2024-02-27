#if !defined(LED_H)
#define LED_H

#include <chrono>
#include <thread>
#include "device.hpp"

class LED: OutputDevice {
private:
  void single_blink(chrono::duration<long double, std::milli> on_time, chrono::duration<long double, std::milli> off_time);

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
