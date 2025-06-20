#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include "rgb_lcd.h"

#define BUTTON_UP_PIN 5
#define BUTTON_DOWN_PIN 6
#define BUTTON_VALIDATE_PIN 7
#define SERIAL_BAUDRATE 9600
#define BUZZER_PIN 3

rgb_lcd lcd;
Servo monServo;
Servo monServo2;
Servo monServo3;
Servo monServofalse;

byte score = 0;
byte lastScore = -1;
byte secretNumber;
byte successCount = 0;
byte failCount = 0;
byte servoState = 0;
bool gameOver = false;

// === Fonctions LCD ===
void printLCD(const char* message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}

void scrollText(const char* message, int row = 0, int delayMs = 300) {
  lcd.clear();
  int len = strlen(message);
  if (len <= 16) {
    lcd.setCursor(0, row);
    lcd.print(message);
    delay(1500);
    return;
  }

  for (int i = 0; i <= len - 16; i++) {
    lcd.setCursor(0, row);
    for (int j = 0; j < 16; j++) {
      lcd.print(message[i + j]);
    }
    delay(delayMs);
  }
  delay(1000);
}

// === Sons ===
void handleScoreChange() {
  if (score == secretNumber) {
    tone(BUZZER_PIN, 300, 50);
    delay(200);
  } else {
    tone(BUZZER_PIN, 130, 20);
    delay(400);
  }
  noTone(BUZZER_PIN);
  delay(25);
}

void playVictoryMelody() {
  playNote(200, 100);
  delay(50);
  playNote(250, 100);
  delay(50);
  playNote(300, 150);
}

void playDefeatMelody() {
  playNote(180, 100);
  delay(50);
  playNote(160, 100);
  delay(50);
  playNote(140, 150);
}

void playNote(int frequency, int duration) {
  tone(BUZZER_PIN, frequency, duration);
  delay(duration * 1.3);
  noTone(BUZZER_PIN);
}

void setup() {
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
  pinMode(BUTTON_VALIDATE_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  lcd.begin(16, 2);
  lcd.setRGB(0, 255, 0);

  randomSeed(analogRead(A0));
  secretNumber = random(0, 21);

  monServo.attach(9);
  monServo2.attach(10);
  monServo3.attach(11);
  monServofalse.attach(12);

  monServo.write(0);
  monServo2.write(0);
  monServo3.write(0);
  monServofalse.write(90);

  scrollText("Devine 3 fois le bon chiffre pour ouvrir le coffre !");
}

void loop() {
  if (gameOver) return;

  static unsigned long lastUpTime = 0;
  static unsigned long lastDownTime = 0;
  static unsigned long lastValidateTime = 0;
  unsigned long now = millis();

  if (digitalRead(BUTTON_UP_PIN) == LOW && now - lastUpTime > 250) {
    if (score < 20) score++;
    lastUpTime = now;
    handleScoreChange();
  }

  if (digitalRead(BUTTON_DOWN_PIN) == LOW && now - lastDownTime > 250) {
    if (score > 0) score--;
    lastDownTime = now;
    handleScoreChange();
  }

  if (digitalRead(BUTTON_VALIDATE_PIN) == LOW && now - lastValidateTime > 250) {
    lastValidateTime = now;

    if (score == secretNumber) {
      successCount++;

      char msg[64];
      sprintf(msg, "Bravo ! %u est correct !", (unsigned int)score);
      scrollText(msg);
      playVictoryMelody();

      if (servoState == 0) monServo.write(90);
      else if (servoState == 1) monServo2.write(90);
      else if (servoState == 2) monServo3.write(90);
      servoState++;

    } else {
      failCount++;

      char msg1[64];
      char msg2[64];
      sprintf(msg1, "Non, %u n'est pas correct.", (unsigned int)score);
      sprintf(msg2, "Le bon nombre etait %u", (unsigned int)secretNumber);
      scrollText(msg1);
      scrollText(msg2);
      playDefeatMelody();
    }

    if (successCount >= 3) {
      scrollText("Felicitations ! Le coffre s'ouvre !");
      playVictoryMelody();
      gameOver = true;

    } else if (failCount >= 3) {
      scrollText("Echec. Le coffre reste ferme.");
      playDefeatMelody();
      monServofalse.write(0);
      gameOver = true;

    } else {
      secretNumber = random(0, 21);
      scrollText("Nouveau nombre secret !");
    }
  }

  if (score != lastScore) {
    char scoreMsg[64];
    sprintf(scoreMsg, "Score actuel : %u", (unsigned int)score);
    scrollText(scoreMsg);
    lastScore = score;
  }
}
