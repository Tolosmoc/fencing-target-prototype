#include <EEPROM.h>
#include "config.h"

void saveHighScore(int addr, int value) {
  EEPROM.put(addr, value);
}

int loadHighScore(int addr) {
  int v;
  EEPROM.get(addr, v);
  return v;
}
