#if !defined(PWM_LED_H)
#define PWM_LED_H

#include "pwm_device.hpp"

class PWMLED : public PWMOutputDevice {
public:
  PWMLED(int pin);
  ~PWMLED();

  void blink(float on_time, float off_time, float fade_in_time, float fade_out_time, int n);
  void pulse(float fade_in_time, float fade_out_time, int n);
};


#endif // PWM_LED_H
