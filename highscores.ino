#include <EEPROM.h>
#include "config.h"

// Store 5 ints (2 bytes each on AVR) => 10 bytes total if int=2 bytes on UNO.
// We'll reserve space starting at address 0.
static const int EEPROM_ADDR_CLASSIC_BASE = 0;

static int addrClassicLevel(int level) {
  if (level < 1) level = 1;
  if (level > 5) level = 5;
  // Each int uses sizeof(int) bytes
  return EEPROM_ADDR_CLASSIC_BASE + (level - 1) * (int)sizeof(int);
}

int loadHighScoreClassicLevel(int level) {
  int v = 0;
  EEPROM.get(addrClassicLevel(level), v);
  // sanity check in case EEPROM is garbage
  if (v < 0 || v > 30000) v = 0;
  return v;
}

void saveHighScoreClassicLevel(int level, int value) {
  int current = loadHighScoreClassicLevel(level);
  if (value > current) {
    EEPROM.put(addrClassicLevel(level), value);
  }
}
