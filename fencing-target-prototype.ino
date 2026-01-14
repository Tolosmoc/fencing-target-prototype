#include "config.h"

GameState state = STATE_MENU;
int score = 0;
int selectedMode = 1;

// forward declarations
void menuLoop();
void classicSetupLoop();
void classicLoop();
void timerLoop();
void memoryLoop();
void speedrunLoop();

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  displayInit();
  displayMessage("READY!", "Press to start");

  randomSeed(analogRead(A0));
}

void loop() {
  switch (state) {
    case STATE_MENU:          menuLoop(); break;
    case STATE_CLASSIC_SETUP: classicSetupLoop(); break;
    case STATE_CLASSIC:       classicLoop(); break;
    case STATE_TIMER:         timerLoop(); break;
    case STATE_MEMORY:        memoryLoop(); break;
    case STATE_SPEEDRUN:      speedrunLoop(); break;
  }
}

