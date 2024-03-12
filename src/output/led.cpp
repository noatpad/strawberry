#include "led.hpp"

LED::LED(int pin): OutputDevice(pin) {}
LED::LED(int pin, int value): OutputDevice(pin, value) {}
LED::LED(int pin, int value, int active_high): OutputDevice(pin, value, active_high) {}

LED::~LED() {}

void LED::blink(double time) { blink(time, time); }
void LED::blink(double on_time, double off_time) { blink(on_time, off_time, 1); }
void LED::blink(double time, int n) { blink(time, time, n); }
void LED::blink(double on_time, double off_time, int n) {
  milliseconds on_time_ms = on_time * 1s, off_time_ms = off_time * 1s;
  for (int i = 0; i < n; i++) {
    on();
    this_thread::sleep_for(on_time_ms);
    off();
    this_thread::sleep_for(off_time_ms);
  };
}
