#include "config.h"

void menuLoop() {
  static int lastShownMode = -1;

  // Refresh screen when changing mode
  if (selectedMode != lastShownMode) {
    displayMenu();
    lastShownMode = selectedMode;
    if (selectedMode == 1) {
      int hs = loadHighScoreClassicLevel(classicLevel);
      // affiche "HS: xxx" sur ligne 2 (à adapter à ton displayMenu)
    }
  }

  int b = readButton();
  if (b == 0) {                 // bouton "rouge" = mode précédent
    selectedMode--;
    if (selectedMode < 1) selectedMode = 4;
  } else if (b == 1) {          // yellow button = next mode
    selectedMode++;
    if (selectedMode > 4) selectedMode = 1;
  } else if (b == 2) {          // blue button = OK
    // launch selected mode
    if (selectedMode == 1) state = STATE_CLASSIC_SETUP;
    if (selectedMode == 2) state = STATE_TIMER;
    if (selectedMode == 3) state = STATE_MEMORY;
    if (selectedMode == 4) state = STATE_SPEEDRUN;
  }
}
