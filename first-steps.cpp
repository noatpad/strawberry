#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
using namespace std;

const unsigned int GPIO_BASE = 0x00200000;
const int GPIO_LEN = 4096;

const int GPSET0 = 7;   // 0x1c
const int GPCLR0 = 10;  // 0x28
const int GPLEV0 = 13;  // 0x34

const unsigned int MODE_INPUT = 0;
const unsigned int MODE_OUTPUT = 1;
const unsigned int MODE_PADDED = 7;

volatile unsigned int *gpio;

int main() {
  // Open gpiomem
  int fd = open("/dev/gpiomem", O_RDWR | O_SYNC);
  if (fd < 0) {
    printf("ERROR - opening gpiomem\n");
    exit(-1);
  }

  // Setup direct GPIO register access
  gpio = (volatile unsigned int*) mmap(NULL, GPIO_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);

  // Close the file, we don't need it anymore
  close(fd);

  if (gpio == MAP_FAILED) {
    printf("ERROR - mapping gpio\n");
    exit(-1);
  }

  // Set a test pin into output mode
  int pin = 4;
  int reg = pin / 10;
  int shift = (pin % 10) * 3;
  gpio[reg] = (gpio[reg] & ~(MODE_PADDED << shift)) | (MODE_OUTPUT << shift);

  // Blink LED a few times
  int level, bank;
  for (int i = 1; i <= 10; i++) {
    // Toggle pin as high or low
    level = i % 2 ? GPSET0 : GPCLR0;
    bank = pin >> 5;
    gpio[level + bank] = 1 << (pin & 31);

    // Print out current GPIO level from GPLEV register
    level = (gpio[GPLEV0 + bank] & (1 << (pin & 31))) != 0;
    printf("Pin %d is level %d\n", pin, level);
    sleep(1);
  }

  // Release register access memory
  munmap((void*) gpio, GPIO_LEN);
}
