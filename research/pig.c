#include <stdio.h>
#include <pigpio.h>

#define LED 4   // GPIO pin number
#define BUTTON 5

int main(void) {
  printf("Blink!\n");

  if (gpioInitialise() < 0) return 1;
  gpioSetMode(LED, PI_OUTPUT);
  gpioSetMode(BUTTON, PI_INPUT);
  gpioSetPullUpDown(BUTTON, PI_PUD_UP);

  // for (int i = 0; i < 10; i++) {
  //   gpioWrite(LED, 1);
  //   gpioDelay(500);
  //   gpioWrite(LED, 0);
  //   gpioDelay(500);
  // }

  while (1) {
    gpioWrite(LED, gpioRead(BUTTON));
  }

  gpioTerminate();
}

// gcc pig.c -lpigpio
// sudo ./a.out
