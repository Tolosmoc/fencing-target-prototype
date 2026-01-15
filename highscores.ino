#include <EEPROM.h>
#include "config.h"

static const int EEPROM_ADDR_CLASSIC_BASE = 0;

static int addrClassicLevel(int level) {
  if (level < 1) level = 1;
  if (level > 5) level = 5;
  return EEPROM_ADDR_CLASSIC_BASE + (level - 1) * (int)sizeof(int);
}

int loadHighScoreClassicLevel(int level) {
  int v = 0;
  EEPROM.get(addrClassicLevel(level), v);
  if (v < 0 || v > 30000) v = 0;
  return v;
}

void saveHighScoreClassicLevel(int level, int value) {
  int current = loadHighScoreClassicLevel(level);
  if (value > current) {
    EEPROM.put(addrClassicLevel(level), value);
  }
}

static const int EEPROM_ADDR_TIMER_BASE =
  EEPROM_ADDR_CLASSIC_BASE + 5 * (int)sizeof(int);

static int addrTimerLevel(int level) {
  if (level < 1) level = 1;
  if (level > 5) level = 5;
  return EEPROM_ADDR_TIMER_BASE + (level - 1) * (int)sizeof(int);
}

int loadHighScoreTimerLevel(int level) {
  int v = 0;
  EEPROM.get(addrTimerLevel(level), v);
  if (v < 0 || v > 30000) v = 0;
  return v;
}

void saveHighScoreTimerLevel(int level, int value) {
  int current = loadHighScoreTimerLevel(level);
  if (value > current) {
    EEPROM.put(addrTimerLevel(level), value);
  }
}

