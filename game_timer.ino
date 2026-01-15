#include "config.h"

static int pickNewTarget(int prev) {
  int t = random(0, 5);
  if (t == prev) t = (t + 1) % 5;
  return t;
}

void timerLoop() {
  static bool first = true;
  static bool finished = false;

  static uint32_t startMs = 0;
  static uint32_t durationMs = 0;
  static int target = -1;

  static uint8_t mult = 1;
  static uint8_t hitsInCycle = 0;
  static const uint8_t HITS_PER_MULT = 15;

  // -------- INIT --------
  if (first) {
    first = false;
    finished = false;

    score = 0;
    mult = 1;
    hitsInCycle = 0;

    durationMs = timerLevelToDurationMs(timerLevel);
    startMs = millis();

    allLedsOff();
    target = pickNewTarget(-1);
    digitalWrite(ledPins[target], HIGH);

    showTimerHUD(score, durationMs, timerLevel, mult, hitsInCycle, HITS_PER_MULT);
  }

  // -------- TIME UP LATCHED SCREEN --------
  if (finished) {
    if (readButton() != -1) {
      first = true;
      state = STATE_MENU;
    }
    return;
  }

  // -------- NORMAL GAMEPLAY --------
  uint32_t now = millis();
  uint32_t elapsed = now - startMs;

  if (elapsed >= durationMs) {
    finished = true;

    allLedsOff();

    saveHighScoreTimerLevel(timerLevel, score);
    int best = loadHighScoreTimerLevel(timerLevel);

    char l1[17], l2[17];
    snprintf(l1, sizeof(l1), "TIME UP! S:%d", score);
    snprintf(l2, sizeof(l2), "Best %d - AAA", best);
    displayMessage(l1, l2);
    return;
  }

  uint32_t remaining = durationMs - elapsed;

  int b = readButton();
  if (b != -1) {
    if (b == target) {
      score += mult;

      hitsInCycle++;
      if (hitsInCycle >= HITS_PER_MULT) {
        hitsInCycle = 0;
        if (mult < 99) mult++; // cap (optional)
      }
    } else {
      mult = 1;
      hitsInCycle = 0;
    }

    digitalWrite(ledPins[target], LOW);
    target = pickNewTarget(target);
    digitalWrite(ledPins[target], HIGH);
  }

  // HUD refresh (throttled)
  static uint32_t lastHud = 0;
  if (now - lastHud >= 80) {
    lastHud = now;
    showTimerHUD(score, remaining, timerLevel, mult, hitsInCycle, HITS_PER_MULT);
  }
}
