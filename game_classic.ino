#include "config.h"

static int currentLed = -1;
static unsigned long startTime = 0;
static unsigned long timeLimit = 2000;
static int lives = 3;
static int hits = 0;
static int mult = 1;
static const int HITS_PER_MULT = 15;
static bool started = false;
int classicLevel = 2;

static unsigned long levelToTimeLimitMs(int level) {
  const unsigned long table[5] = {2500, 2000, 1500, 1000, 500}; // lvl 1 to 5
  if (level < 1) level = 1;
  if (level > 5) level = 5;
  return table[level - 1];
}

static void startRound() {
  allLedsOff();

  int base = 200 + (5 - classicLevel) * 60;
  delay(random(base, base + 300));

  currentLed = random(0, 5);
  digitalWrite(ledPins[currentLed], HIGH);
  startTime = millis();

  displayHUDClassic(lives, score, classicLevel, mult, hits);
}

static void loseLifeQuick() {
  lives--;
  mult = 1;
  hits = 0;
  allLedsOff();

  for (int k = 0; k < 1; k++) {
    for (int i = 0; i < 5; i++) digitalWrite(ledPins[i], HIGH);
    delay(100);
    for (int i = 0; i < 5; i++) digitalWrite(ledPins[i], LOW);
    delay(100);
  }

  if (lives > 0) {
    displayHUDClassic(lives, score, classicLevel, mult, hits);
    startRound();
  } else {
    int hsBefore = loadHighScoreClassicLevel(classicLevel);
    saveHighScoreClassicLevel(classicLevel, score);
    int hsAfter  = loadHighScoreClassicLevel(classicLevel);

    char line1[17];
    char line2[17];

    snprintf(line1, sizeof(line1), "Score: %d", score);

    if (hsAfter > hsBefore) {
      snprintf(line2, sizeof(line2), "BEST:%d NEW!", hsAfter);
    } else {
      snprintf(line2, sizeof(line2), "BEST:%d - AAA", hsBefore);
    }

    displayMessage("GAME OVER", "");
    delay(450);
    displayMessage(line1, line2);
    delay(2000);


    score = 0;
    lives = 3;
    started = false;
    state = STATE_MENU;
  }
}

void startClassic() {
  score = 0;
  lives = 3;
  timeLimit = levelToTimeLimitMs(classicLevel);
  started = true;

  displayMessage("CLASSIC", "Get ready...");
  delay(400);

  startRound();
}

void classicLoop() {
  if (!started) {
    startClassic();
    return;
  }

  if (millis() - startTime > timeLimit) {
    loseLifeQuick();
    return;
  }

  int b = readButton();
  if (b == -1) return;

  digitalWrite(ledPins[currentLed], LOW);

  if (b != currentLed) {
    loseLifeQuick();
    return;
  }

 hits++;
  score += mult;

  if (hits % HITS_PER_MULT == 0) {
    mult++;
  }

  displayHUDClassic(lives, score, classicLevel, mult, hits);

  startRound();
}
