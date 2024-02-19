from time import sleep
import RPi.GPIO as GPIO

led = 7   # BCM pin number

print("Blink!")
GPIO.setmode(GPIO.BOARD)
GPIO.setup(led, GPIO.OUT)

for _ in range(10):
  GPIO.output(led, True)
  sleep(0.5)
  GPIO.output(led, False)
  sleep(0.5)

# python rpidot.py
