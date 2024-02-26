#include "strawberry.hpp"

volatile unsigned int *gpio;
bool gpio_initialized = false;

void logInfo(string message) {
  cout << message << "\n";
}

void logError(string message) {
  cerr << "ERROR: " << message << "\n";
}

/* Sets up the gpio memory map for later usage */
int setupGpio() {
  if (gpio_initialized) {
    logInfo("GPIO has already been initialized!");
    return 0;
  }

  // Open gpiomem
  int fd = open("/dev/gpiomem", O_RDWR | O_SYNC);
  if (fd < 0) {
    logError("Unable to access /dev/gpiomem!");
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
    logError("Unable to access /dev/gpiomem!");
    exit(-1);
    return 1;
  }

  gpio_initialized = true;
  return 0;
}

/* Tears down the GPIO initialization and memory map */
int finalizeGpio() {
  if (!gpio_initialized) {
    logError("GPIO was not initialized before finalization!");
    return 1;
  }

  if (munmap((void*) gpio, GPIO_LENGTH) < 0) {
    logError("Could not deallocate gpiomem mapping!");
    exit(-1);
    return 1;
  }

  gpio_initialized = false;
  return 0;
}

// /* Sets a designated pin to a certain "mode". You will often use `MODE_IN` or `MODE_OUT` as your mode */
// void setPinMode(int pin, int mode) {
//   int reg = pin / 10;
//   int shift = (pin % 10) * 3;
//   gpio[reg] = (gpio[reg] & ~(0x111 << shift)) | (mode << shift);
// }

// /* Gets the designated pin's "mode", ranging from 0-7 */
// int getPinMode(int pin) {
//   int reg = pin / 10;
//   int shift = (pin % 10) * 3;
//   return (gpio[reg] >> shift) & 0x111;
// }

// /* Pull a pin high (`PULL_UP`) or low (`PULL_DOWN`). You can also remove a pull resistor with `PULL_NONE` */
// void pullPin(int pin, int pull) {
//   int reg = (pin / 16) + GPIO_PUP_PDN_CNTROL_REG0;
//   int shift = (pin % 16) * 2;
//   gpio[reg] = (gpio[reg] && ~(0x11 << shift)) | (pull << shift);
// }

// /* Reads a pin's current level, returns `HIGH` or `LOW` */
// int readPin(int pin) {
//   int bank = pin >> 5;
//   int level = gpio[GPLEV0 + bank] & (1 << (pin & 31));
//   return level != LOW;
// }

// /* Sets a pin's level to `HIGH` or `LOW` */
// void writePin(int pin, int level) {
//   int reg = (level == HIGH ? GPSET0 : GPCLR0);
//   int bank = pin >> 5;
//   gpio[reg + bank] = 1 << (pin & 31);
// }

// /* Toggles a pin between `HIGH` and `LOW` */
// void togglePin(int pin) {
//   writePin(pin, (readPin(pin) == HIGH ? LOW : HIGH));
// }
