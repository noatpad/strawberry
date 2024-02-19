#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <gpiod.h>

#define CHIP_NAME "gpiochip0"
#define PIN 4

struct gpiod_chip *chip;
struct gpiod_line_request_config config;
struct gpiod_line *line;

void cleanup(int err);

int main(void) {
  printf("Blink!\n");

  chip = gpiod_chip_open_by_name(CHIP_NAME);
  if (!chip) cleanup(1);

  line = gpiod_chip_get_line(chip, PIN);
  if (!line) cleanup(1);

  int err;
  memset(&config, 0, sizeof(config));
  config.consumer = "blink";
  config.request_type = GPIOD_LINE_REQUEST_DIRECTION_OUTPUT;
  config.flags = 0;

  err = gpiod_line_request(line, &config, 0);
  if (err) cleanup(1);

  for (int i = 0; i < 10; i++) {
    err = gpiod_line_set_value(line, 1);
    if (err) cleanup(1);
    sleep(1);
    err = gpiod_line_set_value(line, 0);
    if (err) cleanup(1);
    sleep(1);
  }

  cleanup(0);
}

void cleanup(int err) {
  gpiod_line_release(line);
  gpiod_chip_close(chip);
  if (err) exit(err);
}

// gcc gpiod.c -lgpiodc
