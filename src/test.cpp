#include "strawberry.hpp"

const int LED = 4;
const int BUTTON = 17;

int main() {
  setupGpio();

  setPinMode(LED, MODE_OUT);
  setPinMode(BUTTON, MODE_IN);
  pullPin(BUTTON, PULL_DOWN);

  // for (int i = 0; i <= 10; i++) {
  //   togglePin(LED);
  //   printf("Pin %d is level %d\n", LED, readPin(LED));
  //   sleep(1);
  // }

  int is_pressed;
  while (1) {
    is_pressed = readPin(BUTTON);
    printf("%d\n", is_pressed);
    writePin(LED, is_pressed);
  }

  finalizeGpio();
}
