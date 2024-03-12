#if !defined(BUZZER_H)
#define BUZZER_H

#include "device.hpp"

const float DEFAULT_BEEP_TIME = 1;

class Buzzer : public OutputDevice {
public:
  Buzzer(int pin);
  ~Buzzer();

  void beep();
  void beep(float time);
  void beep(float time, int n);
  void beep(float on_time, float off_time, int n);
};

#endif // BUZZER_H
