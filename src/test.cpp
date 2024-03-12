#include "strawberry.hpp"

int main() {
  // LED led(4);
  // Button button(5);

  // while (1) {
  //   if (button.is_pressed()) break;
  //   led.blink(0.5, 1);
  // }

  PWMOutputDevice led(4);

  for (int i = 0; i <= 10; i++) {
    led.hold((float) i * 0.1, 0.1);
  }
  led.fade(1, 0, 1);
  led.fade(1, 1, 0);
}
