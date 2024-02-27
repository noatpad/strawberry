#include "strawberry.hpp"

int main() {
  LED led(4);
  Button button(5);

  while (1) {
    if (button.is_pressed()) break;
    led.blink(0.5, 1);
  }
}
