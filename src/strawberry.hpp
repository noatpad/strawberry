#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

const unsigned int GPIO_BASE = 0x00200000;
const int GPIO_LENGTH = 4096;

const int GPSET0 = 7;
const int GPCLR0 = 10;
const int GPLEV0 = 13;

const int MODE_IN = 0;
const int MODE_OUT = 1;
const int MODE_ALT0 = 2;
const int MODE_ALT1 = 3;
const int MODE_ALT2 = 4;
const int MODE_ALT3 = 5;
const int MODE_ALT4 = 6;
const int MODE_ALT5 = 7;

const int LOW = 0;
const int HIGH = 1;

void logError(char *message);
int setupGpio();
int finalizeGpio();

void setPinMode(int pin, int mode);
int getPinMode(int pin);
int readPin(int pin);
void writePin(int pin, int level);
void togglePin(int pin);
