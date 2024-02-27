#include "strawberry.hpp"

int main() {
  LED led(4);
  // InputDevice button(5);
  // button.pull(PULL_UP);

  // while (1) {
  //   led.toggle();
  //   sleep(1);
  // }

  led.blink(0.5, 10);
}
