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

  // Prepare teardown on exit
  gpio_initialized = true;
  atexit([]{ finalizeGpio(); });
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
