#include "config.h"

static int currentLed = -1;
static unsigned long startTime = 0;
static unsigned long timeLimit = 2000;   // tu peux le rendre dynamique si tu veux
static int lives = 3;
static bool started = false;
int classicLevel = 2;

static unsigned long levelToTimeLimitMs(int level) {
  // 1..5 => 2500, 2000, 1500, 1000, 500
  const unsigned long table[5] = {2500, 2000, 1500, 1000, 500};
  if (level < 1) level = 1;
  if (level > 5) level = 5;
  return table[level - 1];
}

static void allLedsOff() {
  for (int i = 0; i < 5; i++) digitalWrite(ledPins[i], LOW);
}

static void startRound() {
  allLedsOff();

  // petite pause aléatoire entre deux LEDs (comme tu voulais)
  int base = 200 + (5 - classicLevel) * 60;
  delay(random(base, base + 300));

  currentLed = random(0, 5);
  digitalWrite(ledPins[currentLed], HIGH);
  startTime = millis();

  displayHUDClassic(lives, score, classicLevel);
}

static void loseLifeQuick() {
  lives--;
  allLedsOff();

  // Flash rapide = feedback immédiat
  for (int k = 0; k < 2; k++) {
    for (int i = 0; i < 5; i++) digitalWrite(ledPins[i], HIGH);
    delay(90);
    for (int i = 0; i < 5; i++) digitalWrite(ledPins[i], LOW);
    delay(90);
  }

  if (lives > 0) {
    // Pas d’écran "Wrong" long : on réaffiche HUD et on repart
    displayHUDClassic(lives, score, classicLevel);
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

  // Timeout => perte de vie
  if (millis() - startTime > timeLimit) {
    loseLifeQuick();
    return;
  }

  int b = readButton();
  if (b == -1) return;

  // on éteint la LED active dès qu'il y a un input
  digitalWrite(ledPins[currentLed], LOW);

  // Mauvais bouton => perte de vie
  if (b != currentLed) {
    loseLifeQuick();
    return;
  }

  // Bon bouton => +1 score, round suivant
  score++;
  displayHUDClassic(lives, score, classicLevel);

  // round suivant
  startRound();
}
