#include "config.h"

static int currentLed = -1;
static unsigned long startTime;
static const unsigned long timeLimit = 2000;

void startClassic() {
  score = 0;
  currentLed = random(0, 5);
  digitalWrite(ledPins[currentLed], HIGH);
  startTime = millis();
  displayMessage("CLASSIC START");
}

void classicLoop() {
  static bool started = false;

  if (!started) {
    startClassic();
    started = true;
  }

  if (millis() - startTime > timeLimit) {
    displayMessage("TIME OUT");
    state = STATE_MENU;
    started = false;
    return;
  }

  int b = readButton();
  if (b != -1) {
    digitalWrite(ledPins[currentLed], LOW);

    if (b == currentLed) {
      score++;
      displayScore();
      if (score >= 11) {
        digitalWrite(ledPins[currentLed], LOW);
        victorySequence();
        state = STATE_MENU;
        started = false;
        return;
      }
      delay(random(200, 600));
      currentLed = random(0, 5);
      digitalWrite(ledPins[currentLed], HIGH);
      startTime = millis();
    } else {
      displayMessage("WRONG!");
      state = STATE_MENU;
      started = false;
    }
  }
}

static void victorySequence() {
  displayMessage("VICTORY!", "Well played :)");

  for (int i = 0; i < 5; i++) digitalWrite(ledPins[i], LOW);

  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(300);
  }

  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < 5; i++) digitalWrite(ledPins[i], LOW);
    delay(300);
    for (int i = 0; i < 5; i++) digitalWrite(ledPins[i], HIGH);
    delay(300);
  }

  for (int i = 0; i < 5; i++) digitalWrite(ledPins[i], HIGH);

  delay(1500);
}
