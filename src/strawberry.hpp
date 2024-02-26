#ifndef STRAWBERRY_H
#define STRAWBERRY_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "devices.hpp"
using namespace std;

// gpiomem constants
const unsigned int GPIO_BASE = 0x00200000;
const int GPIO_LENGTH = 4096;

// Singleton vars
extern volatile unsigned int *gpio;
extern bool gpio_initialized;

void logInfo(string message);
void logError(string message);
int setupGpio();
int finalizeGpio();

// void setPinMode(int pin, int mode);
// int getPinMode(int pin);
// void pullPin(int pin, int pull);
// int readPin(int pin);
// void writePin(int pin, int level);
// void togglePin(int pin);

#endif
