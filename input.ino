#include "config.h"

int readButton() {
  for (int i = 0; i < 5; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      while (digitalRead(buttonPins[i]) == LOW);
      delay(20);
      return i;
    }
  }
  return -1;
}
