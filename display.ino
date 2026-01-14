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

void displayHUDClassic(int lives, int scoreVal, int level) {
  lcd.setCursor(0, 0);
  lcd.print("L");
  lcd.print(level);
  lcd.print(" ");

  // 3 coeurs (plein si encore en vie, sinon espace)
  for (int i = 0; i < 3; i++) {
    if (i < lives) lcd.write(byte(0)); // coeur
    else lcd.print(" ");
  }

  // Compléter la ligne si restes de caractères (évite artefacts)
  lcd.print("        "); 

  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(scoreVal);
  lcd.print("        ");
}
