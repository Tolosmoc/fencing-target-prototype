#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// LEDs + buttons
// white, red, green, blue, yellow
const int ledPins[5]    = {2, 3, 4, 5, 6};
const int buttonPins[5] = {7, 8, 9, 10, 11};

// LCD 1602 (4-bit mode)
const int LCD_RS = 12;
const int LCD_E  = 13;
const int LCD_D4 = A0;
const int LCD_D5 = A1;
const int LCD_D6 = A2;
const int LCD_D7 = A3;

// Game states
enum GameState {
  STATE_MENU,
  STATE_CLASSIC_SETUP,
  STATE_CLASSIC,
  STATE_TIMER_SETUP,
  STATE_TIMER,
  STATE_MEMORY,
  STATE_SPEEDRUN
};

extern GameState state;
extern int score;
extern int selectedMode;
extern int classicLevel;
extern int timerLevel;

// Display API
void displayInit();
void displayMenu();
void displayScore();
void displayMessage(const char* line1, const char* line2 = "");

// High score API (Classic)
int loadHighScoreClassicLevel(int level);
void saveHighScoreClassicLevel(int level, int value);
void displayHUDClassic(int lives, int scoreVal, int level, int mult, int hits);

void allLedsOff();
uint32_t timerLevelToDurationMs(int lvl);

void timerSetupLoop();
void timerLoop();

void showTimerSetupScreen(uint8_t lvl, uint32_t durationMs);
void showTimerHUD(uint16_t scoreVal, uint32_t remainingMs, uint8_t lvl, uint8_t mult, uint8_t hitInCycle, uint8_t hitsPerMult);

int loadHighScoreTimerLevel(int level);
void saveHighScoreTimerLevel(int level, int value);

#endif
