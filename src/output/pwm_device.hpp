#if !defined(PWM_OUTPUT_DEVICE_H)
#define PWM_OUTPUT_DEVICE_H

#include "device.hpp"

const int DEFAULT_FREQUENCY = 100;

class PWMOutputDevice : public OutputDevice {
private:
  int freq;
  float cycle_time;
  milliseconds cycle_time_ms;

public:
  PWMOutputDevice(int pin);
  PWMOutputDevice(int pin, int _freq);
  ~PWMOutputDevice();

  float read_pwm();
  void hold(float value);
  void hold(float value, float secs);
  void fade(float secs);
  void fade(float secs, float value);
  void fade(float secs, float start, float end);
};

#endif // PWM_OUTPUT_DEVICE_H
