#include "strawberry.hpp"

int main() {
  PWMLED led(4);
  Buzzer buzzer(17);

  cout << "Beep!" << endl;
  buzzer.beep();
  cout << "Blink!" << endl;
  led.blink(1, 1, 0, 0, 3);
  cout << "Beep!" << endl;
  buzzer.beep(0.5);
  cout << "Blink!" << endl;
  led.blink(1, 1, 1, 1, 3);
  cout << "Beep!" << endl;
  buzzer.beep(0.5);
  cout << "Blink!" << endl;
  led.pulse(1, 1, 3);
  cout << "Beep!" << endl;
  buzzer.beep(0.3, 2);
}
