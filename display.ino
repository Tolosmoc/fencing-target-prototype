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

  lcd.createChar(0, heart); // char custom index 0

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


