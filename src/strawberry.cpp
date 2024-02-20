#include "strawberry.hpp"

volatile unsigned int *gpio;

void logError(const char *message) {
  fprintf(stderr, message);
}

/* Sets up the gpio memory map for later usage */
int setupGpio() {
  // Open gpiomem
  int fd = open("/dev/gpiomemaaa", O_RDWR | O_SYNC);
  if (fd < 0) {
    logError("ERROR: Unable to access /dev/gpiomem!\n");
    exit(-1);
    return 1;
  }

  // Set up GPIO register access (and close gpiomem file)
  gpio = (volatile unsigned int*) mmap(
    NULL,
    GPIO_LENGTH,
    PROT_READ | PROT_WRITE,
    MAP_SHARED,
    fd,
    GPIO_BASE
  );
  close(fd);

  if (gpio == MAP_FAILED) {
    logError("ERROR: Unable to access /dev/gpiomem!\n");
    exit(-1);
    return 1;
  }

  return 0;
}

/* Tears down the GPIO initialization and memory map */
int finalizeGpio() {
  if (munmap((void*) gpio, GPIO_LENGTH) < 0) {
    logError("ERROR: Could not deallocate gpiomem mapping!\n");
    exit(-1);
    return 1;
  }

  return 0;
}

/* Sets a designated pin to a certain "mode". You will often use `MODE_IN` or `MODE_OUT` as your mode */
void setPinMode(int pin, int mode) {
  int reg = pin / 10;
  int shift = (pin % 10) * 3;
  gpio[reg] = (gpio[reg] & ~(0x111 << shift)) | (mode << shift);
}

/* Gets the designated pin's "mode", ranging from 0-7 */
int getPinMode(int pin) {
  int reg = pin / 10;
  int shift = (pin % 10) * 3;
  return (gpio[reg] >> shift) & 0x111;
}

/* Reads a pin's current level, returns `HIGH` or `LOW` */
int readPin(int pin) {
  int bank = pin >> 5;
  int level = gpio[GPLEV0 + bank] & (1 << (pin & 31));
  return level != LOW;
}

/* Sets a pin's level to `HIGH` or `LOW` */
void writePin(int pin, int level) {
  int reg = (level == HIGH ? GPSET0 : GPCLR0);
  int bank = pin >> 5;
  gpio[reg + bank] = 1 << (pin & 31);
}

/* Toggles a pin between `HIGH` and `LOW` */
void togglePin(int pin) {
  writePin(pin, (readPin(pin) == HIGH ? LOW : HIGH));
}
