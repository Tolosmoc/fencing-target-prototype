const int ledPins[5] = {2, 3, 4, 5, 6}; // white, red, green, blue, yellow
const int buttonPins[5] = {7, 8, 9, 10, 11};
const int segPins[7] = {12, A0, A1, A2, A3, A4, A5};

// 7-segment digit map
byte digits[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

int score = 0;
int currentLed = -1;
unsigned long startTime;
const unsigned long timeLimit = 2000;

void showDigit(int num) {
  if(num>9) num=9;
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digits[num][i]);
  }
}

void pickNextLed() {
  currentLed = random(0, 5);
  digitalWrite(ledPins[currentLed], HIGH);
  startTime = millis();
}

void victorySequence() {
  Serial.println("!!! VICTORY SEQUENCE !!!");

  for(int i=0;i<5;i++){
    digitalWrite(ledPins[i], HIGH);
    delay(300);
  }

  for(int j=0;j<5;j++){
    for(int i=0;i<5;i++) digitalWrite(ledPins[i], LOW);
    delay(300);
    for(int i=0;i<5;i++) digitalWrite(ledPins[i], HIGH);
    delay(300);
  }

  while(true); // stop game
}

void gameOver() {
  for (int i = 0; i < 5; i++) digitalWrite(ledPins[i], LOW);
  Serial.println("Game Over!");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) digitalWrite(ledPins[j], HIGH);
    delay(300);
    for (int j = 0; j < 5; j++) digitalWrite(ledPins[j], LOW);
    delay(300);
  }
  while(true); // stop game
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A6));

  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  for (int i = 0; i < 7; i++) pinMode(segPins[i], OUTPUT);

  showDigit(0);
  Serial.println("Reaction Game Started!");
  pickNextLed();
}

void loop() {
  if (millis() - startTime > timeLimit) {
    Serial.println("Timeout! LED not pressed in time.");
    gameOver();
  }

  for (int i = 0; i < 5; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      digitalWrite(ledPins[currentLed], LOW);
      
      // Serial Monitor
      switch(i) {
        case 0: Serial.print("Button pressed: White "); break;
        case 1: Serial.print("Button pressed: Red   "); break;
        case 2: Serial.print("Button pressed: Green "); break;
        case 3: Serial.print("Button pressed: Blue  "); break;
        case 4: Serial.print("Button pressed: Yellow"); break;
      }

      if (i == currentLed) {
        score++;
        Serial.print(" ✅ Correct! Score: ");
        Serial.println(score);
        showDigit(score);

        if(score >= 9){
          victorySequence();
        }

        delay(300);
        pickNextLed();
      } else {
        Serial.println(" ❌ Wrong button!");
        gameOver();
      }

      while(digitalRead(buttonPins[i]) == LOW);
      delay(50);
    }
  }
}
