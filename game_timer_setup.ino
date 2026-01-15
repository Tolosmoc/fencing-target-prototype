#include "config.h"

int timerLevel = 1;

void timerSetupLoop() {
  static bool first = true;

  if (first) {
    first = false;
    showTimerSetupScreen(timerLevel, timerLevelToDurationMs(timerLevel));
  }

  int b = readButton();
  if (b == -1) return;

  if (b == 0) { // red => level -
    timerLevel--;
    if (timerLevel < 1) timerLevel = 5;
    showTimerSetupScreen(timerLevel, timerLevelToDurationMs(timerLevel));
  }
  else if (b == 1) { // yellow => level +
    timerLevel++;
    if (timerLevel > 5) timerLevel = 1;
    showTimerSetupScreen(timerLevel, timerLevelToDurationMs(timerLevel));
  }
  else if (b == 2) { // green => OK
    first = true;
    state = STATE_TIMER;
  }
  else if (b == 3) { // blue => BACK
    first = true;
    state = STATE_MENU;
  }
}
