#include "config.h"

void timerLoop() {
  displayMessage("TIMER MODE");
  delay(1000);
  state = STATE_MENU;
}
