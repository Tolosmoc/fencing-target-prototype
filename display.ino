#include <LiquidCrystal.h>
#include "config.h"

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void displayInit() {
  lcd.begin(16, 2);

  byte heart[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
  };

  lcd.createChar(0, heart);

  lcd.clear();
  lcd.print("Boot...");
}

void displayMessage(const char* line1, const char* line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void displayScore() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Score: ");
  lcd.print(score);
}

void displayMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select mode:");

  lcd.setCursor(0, 1);
  switch (selectedMode) {
    case 1: lcd.print("> Classic"); break;
    case 2: lcd.print("> Timer"); break;
    case 3: lcd.print("> Memory"); break;
    case 4: lcd.print("> Speedrun"); break;
    default: lcd.print("> Classic"); break;
  }
}

void displayHUDClassic(int lives, int scoreVal, int level, int mult, int hits) {
  char line0[17];
  char line1[17];

  const int HITS_PER_MULT = 15;
  int prog = hits % HITS_PER_MULT;

  for (int i = 0; i < 16; i++) line0[i] = ' ';
  line0[16] = '\0';

  line0[0] = 'l'; line0[1] = 'v'; line0[2] = 'l'; line0[3] = ':';
  line0[4] = char('0' + level);
  line0[5] = ' ';

  snprintf(&line0[10], 7, "%02d/15", prog);

  snprintf(line1, sizeof(line1), "Score:%-6d x%-2d", scoreVal, mult);
  int len = strlen(line1);
  for (int i = len; i < 16; i++) line1[i] = ' ';
  line1[16] = '\0';

  lcd.setCursor(0, 0);
  lcd.print(line0);

  lcd.setCursor(6, 0);
  for (int i = 0; i < 3; i++) {
    if (i < lives) lcd.write(byte(0));
    else lcd.print(' ');
  }

  lcd.setCursor(0, 1);
  lcd.print(line1);
}

static void lcdWrite16(uint8_t row, const char* s) {
  char buf[17];
  for (int i = 0; i < 16; i++) buf[i] = ' ';
  buf[16] = '\0';

  for (int i = 0; i < 16 && s && s[i]; i++) buf[i] = s[i];

  lcd.setCursor(0, row);
  lcd.print(buf);
}

static void formatMMSSCC(uint32_t ms, char out[9]) {
  // MM:SS:CC
  uint32_t totalCs = ms / 10UL;
  uint8_t cs = totalCs % 100U;
  uint32_t totalSec = totalCs / 100U;
  uint8_t ss = totalSec % 60U;
  uint8_t mm = (totalSec / 60U) % 100U;
  snprintf(out, 9, "%02u:%02u:%02u", mm, ss, cs);
}

void showTimerSetupScreen(uint8_t lvl, uint32_t durationMs) {
  char l1[17], l2[17];
  char t[6];

  // MM:SS
  uint32_t sec = durationMs / 1000UL;
  uint8_t mm = sec / 60U;
  uint8_t ss = sec % 60U;
  snprintf(t, sizeof(t), "%02u:%02u", mm, ss);

  int best = loadHighScoreTimerLevel(lvl);

  snprintf(l1, sizeof(l1), "Timer lvl%u:%s", lvl, t);

  snprintf(l2, sizeof(l2), "Best %d - AAA", best);

  lcdWrite16(0, l1);
  lcdWrite16(1, l2);
}


void showTimerHUD(uint16_t scoreVal, uint32_t remainingMs, uint8_t lvl, uint8_t mult, uint8_t hitInCycle, uint8_t hitsPerMult) {
  char l1[17], l2[17];
  char t[9];
  formatMMSSCC(remainingMs, t);

  char right1[9];
  snprintf(right1, sizeof(right1), "Lvl%u", lvl);
  snprintf(l1, sizeof(l1), "%s%8s", t, right1);

  char left2[9];
  snprintf(left2, sizeof(left2), "S:%u", scoreVal);

  char right2[9];
  snprintf(right2, sizeof(right2), "x%u %02u/%02u", mult, hitInCycle, hitsPerMult);

  snprintf(l2, sizeof(l2), "%-8s%8s", left2, right2);

  lcdWrite16(0, l1);
  lcdWrite16(1, l2);
}
