#if !defined(CONTROLLER_H)
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

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

#endif
