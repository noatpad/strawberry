#include "strawberry.hpp"

const int LED = 4;

int main() {
  setupGpio();

  setPinMode(LED, MODE_OUT);
  for (int i = 0; i <= 10; i++) {
    togglePin(LED);
    printf("Pin %d is level %d\n", LED, readPin(LED));
    sleep(1);
  }

  finalizeGpio();
}
