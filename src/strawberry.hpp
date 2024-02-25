#ifndef STRAWBERRY_H
#define STRAWBERRY_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
using namespace std;

// /dev/gpiomem constants
const unsigned int GPIO_BASE = 0x00200000;
const int GPIO_LENGTH = 4096;

// Register memory offsets
const int GPSET0 = 7;                       // 0x1c
const int GPCLR0 = 10;                      // 0x28
const int GPLEV0 = 13;                      // 0x34
const int GPIO_PUP_PDN_CNTROL_REG0 = 57;    // 0xe4

// Pin modes
const int MODE_IN = 0;
const int MODE_OUT = 1;
const int MODE_ALT0 = 2;
const int MODE_ALT1 = 3;
const int MODE_ALT2 = 4;
const int MODE_ALT3 = 5;
const int MODE_ALT4 = 6;
const int MODE_ALT5 = 7;

// Pull up/down options
const int PULL_NONE = 0;
const int PULL_UP = 1;
const int PULL_DOWN = 2;

// LOW/HIGH constants
const int LOW = 0;
const int HIGH = 1;

void logInfo(string message);
void logError(string message);
int setupGpio();
int finalizeGpio();

void setPinMode(int pin, int mode);
int getPinMode(int pin);
void pullPin(int pin, int pull);
int readPin(int pin);
void writePin(int pin, int level);
void togglePin(int pin);

#endif
