#include "strawberry.hpp"

int main() {
  PWMLED led(4);
  led.blink(1, 1, 0, 0, 3);
  led.blink(1, 1, 1, 1, 3);
  led.pulse(1, 1, 3);
}
