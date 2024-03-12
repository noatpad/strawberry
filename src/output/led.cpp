#include "led.hpp"

LED::LED(int pin): OutputDevice(pin) {}
LED::LED(int pin, int value): OutputDevice(pin, value) {}
LED::LED(int pin, int value, int active_high): OutputDevice(pin, value, active_high) {}

LED::~LED() {}

void LED::single_blink(milliseconds on_time, milliseconds off_time) {
  on();
  this_thread::sleep_for(on_time);
  off();
  this_thread::sleep_for(off_time);
}

void LED::blink(double time) { blink(time, time); }
void LED::blink(double on_time, double off_time) { blink(on_time, off_time, 1); }
void LED::blink(double time, int n) { blink(time, time, n); }
void LED::blink(double on_time, double off_time, int n) {
  milliseconds da = on_time * 1s, db = off_time * 1s;
  for (int i = 0; i < n; i++) single_blink(da, db);
}
