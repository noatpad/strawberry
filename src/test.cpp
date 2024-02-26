#include "strawberry.hpp"

int main() {
  OutputDevice led(4);
  InputDevice button(5);
  button.pull(PULL_UP);

  while (1) {
    led.write(button.read());
  }

  finalizeGpio();
}
