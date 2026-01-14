#include "config.h"

void showClassicSetupScreen() {
  int hs = loadHighScoreClassicLevel(classicLevel);

  char l1[17];
  char l2[17];

  snprintf(l1, sizeof(l1), "Classic  lvl:%d", classicLevel);
  snprintf(l2, sizeof(l2), "BEST:%d - AAA", hs);

  displayMessage(l1, l2);
}

void classicSetupLoop() {
  static bool first = true;
  if (first) {
    showClassicSetupScreen();
    first = false;
  }

  int b = readButton();
  if (b == -1) return;

  if (b == 0) {                 // level -
    classicLevel--;
    if (classicLevel < 1) classicLevel = 5;
    showClassicSetupScreen();
  }
  else if (b == 1) {            // level +
    classicLevel++;
    if (classicLevel > 5) classicLevel = 1;
    showClassicSetupScreen();
  }
  else if (b == 2) {            // OK
    first = true;
    state = STATE_CLASSIC;
  }
  else if (b == 3) {            // BACK
    first = true;
    state = STATE_MENU;
  }
}
