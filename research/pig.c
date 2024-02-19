#include <stdio.h>
#include <pigpio.h>

#define LED 4   // GPIO pin number

int main(void) {
  printf("Blink!\n");

  if (gpioInitialise() < 0) return 1;
  gpioSetMode(LED, PI_OUTPUT);

  for (int i = 0; i < 10; i++) {
    gpioWrite(LED, 1);
    gpioDelay(500);
    gpioWrite(LED, 0);
    gpioDelay(500);
  }

  gpioTerminate();
}

// gcc pig.c -lpigpio
// sudo ./a.out
