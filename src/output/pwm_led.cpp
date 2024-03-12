#include "pwm_led.hpp"

PWMLED::PWMLED(int pin): PWMOutputDevice(pin) {}

PWMLED::~PWMLED() {}

void PWMLED::blink(float on_time, float off_time, float fade_in_time, float fade_out_time, int n) {
  off();
  for (int i = 0; i < n; i++) {
    fade(fade_in_time, LOW, HIGH);
    hold(HIGH, on_time);
    fade(fade_out_time, HIGH, LOW);
    hold(LOW, off_time);
  }
}

void PWMLED::pulse(float fade_in_time, float fade_out_time, int n) {
  off();
  for (int i = 0; i < n; i++) {
    fade(fade_in_time, LOW, HIGH);
    fade(fade_out_time, HIGH, LOW);
  }
}
