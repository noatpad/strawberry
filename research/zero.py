from time import sleep
from gpiozero import LED

print("Blink!")
led = LED(4)    # GPIO pin number

for _ in range(10):
  led.on()
  sleep(0.5)
  led.off()
  sleep(0.5)

# python zero.py
