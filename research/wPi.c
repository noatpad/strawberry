#include <stdio.h>
#include <wiringPi.h>

#define LED 7   // BCM pin number

int main(void) {
  printf("Blink!\n");

  if (wiringPiSetup() < 0) return 1;
  pinMode(LED, OUTPUT);

  for (int i = 0; i < 10; i++) {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
}

// gcc wPi.c -lwiringPi
