#include "config.h"

void allLedsOff() {
  for (int i = 0; i < 5; i++) digitalWrite(ledPins[i], LOW);
}

uint32_t timerLevelToDurationMs(int lvl) {
  switch (lvl) {
    case 1: return 30000UL;    // 0:30
    case 2: return 60000UL;    // 1:00
    case 3: return 90000UL;    // 1:30
    case 4: return 120000UL;   // 2:00
    case 5: return 150000UL;   // 2:30
    default: return 60000UL;
  }
}
