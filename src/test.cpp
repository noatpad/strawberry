#include "strawberry.hpp"

int main() {
  PWMLED led(4);
  Buzzer buzzer(17);

  buzzer.beep();
  led.blink(1, 1, 0, 0, 3);
  buzzer.beep(0.5);
  led.blink(1, 1, 1, 1, 3);
  buzzer.beep(0.5);
  led.pulse(1, 1, 3);
  buzzer.beep(0.3, 2);
}
