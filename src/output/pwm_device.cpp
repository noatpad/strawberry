#include "pwm_device.hpp"

PWMOutputDevice::PWMOutputDevice(int pin): PWMOutputDevice(pin, DEFAULT_FREQUENCY) {}
PWMOutputDevice::PWMOutputDevice(int pin, int _freq): OutputDevice(pin), freq(_freq) {
  cycle_time = 1.0 / freq;
  cycle_time_ms = cycle_time * 1s;
}

PWMOutputDevice::~PWMOutputDevice() {}

// May be buggy
float PWMOutputDevice::read_pwm() {
  int ons = 0;
  for (int i = 0; i < freq; i++) {
    if (read()) ons++;
    this_thread::sleep_for(cycle_time_ms);
  }
  return (float) ons / freq;
}

void PWMOutputDevice::hold(float value) { hold(value, cycle_time); }
void PWMOutputDevice::hold(float value, float secs) {
  float on_time = value * cycle_time;
  float off_time = cycle_time - on_time;
  milliseconds on_time_ms = on_time * 1s, off_time_ms = off_time * 1s;

  for (float i = 0.0; i < secs; i += cycle_time) {
    on();
    this_thread::sleep_for(on_time_ms);
    off();
    this_thread::sleep_for(off_time_ms);
  }
}

void PWMOutputDevice::fade(float secs) { fade(secs, 1.0); }
void PWMOutputDevice::fade(float secs, float target) { fade(secs, read_pwm(), target); }
void PWMOutputDevice::fade(float secs, float start, float end) {
  int cycles = secs / cycle_time;
  float step = (end - start) / cycles;
  for (int i = 0; i < cycles; i++) hold(start + (step * i));
  hold(end);
}
