#include <LiquidCrystal.h>
#include "config.h"

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void displayInit() {
  lcd.begin(16, 2);
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
