#include "buzzer.hpp"

Buzzer::Buzzer(int pin): OutputDevice(pin) {}
Buzzer::~Buzzer() {}

void Buzzer::beep() { beep(DEFAULT_BEEP_TIME); }
void Buzzer::beep(float time) { beep(time, 1); }
void Buzzer::beep(float time, int n) { beep(time, time, n); }
void Buzzer::beep(float on_time, float off_time, int n) {
  if (n <= 0) return;
  milliseconds on_time_ms = on_time * 1s, off_time_ms = off_time * 1s;

  on();
  this_thread::sleep_for(on_time_ms);
  if (off_time > 0) {
    for (int i = 1; i < n; i++) {
      off();
      this_thread::sleep_for(off_time_ms);
      on();
      this_thread::sleep_for(on_time_ms);
    }
  }
  off();
}
