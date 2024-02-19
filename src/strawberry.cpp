#include "strawberry.hpp"

volatile unsigned int *gpio;

void logError(char *message) {
  fprintf(stderr, message);
}

int setupGpio() {
  // Open gpiomem
  int fd = open("/dev/gpiomem", O_RDWR | O_SYNC);
  if (fd < 0) {
    fprintf(stderr, "ERROR: Unable to access /dev/gpiomem!\n");
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
    fprintf(stderr, "ERROR: Unable to access /dev/gpiomem!\n");
    exit(-1);
    return 1;
  }

  return 0;
}

int finalizeGpio() {
  if (munmap((void*) gpio, GPIO_LENGTH) < 0) {
    fprintf(stderr, "ERROR: Could not deallocate gpiomem mapping!\n");
    exit(-1);
    return 1;
  }

  return 0;
}

void setPinMode(int pin, int mode) {
  int reg = pin / 10;
  int shift = (pin % 10) * 3;
  gpio[reg] = (gpio[reg] & ~(0x111 << shift)) | (mode << shift);
}

int readPin(int pin) {
  int bank = pin >> 5;
  int level = gpio[GPLEV0 + bank] & (1 << (pin & 31));
  return level != LOW;
}

void writePin(int pin, int level) {
  int reg = (level == HIGH ? GPSET0 : GPCLR0);
  int bank = pin >> 5;
  gpio[reg + bank] = 1 << (pin & 31);
}

void togglePin(int pin) {
  int level = readPin(pin);
  level = (level == HIGH ? LOW : HIGH);
  writePin(pin, level);
}
