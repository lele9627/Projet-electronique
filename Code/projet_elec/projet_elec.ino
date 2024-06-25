#include "SevSeg.h"
SevSeg sevseg;

#define PIR A5
#define LED 13
#define BUZZER 14 // Définir la broche A0 comme sortie numérique
int score = 0;
//const int sensitivity = 50; 

enum DetectionState { IDLE, DETECTED, DEBOUNCING };
DetectionState state = IDLE;

void setup(){
  Serial.begin(9600);
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT); // Configurer la broche du buzzer comme sortie

  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};

  bool resistorsOnSegments = true; 
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void loop(){
  int pirVal = digitalRead(PIR);
  sevseg.setNumber(score);
  sevseg.refreshDisplay();

  switch (state) {
    case IDLE:
      if (pirVal == HIGH) {
        state = DETECTED;
        digitalWrite(LED, HIGH);
        tone(BUZZER, 1000); // Émettre un son de 1000 Hz
        Serial.println("je t'ai vu ");
      }
      break;

    case DETECTED:
      if (pirVal == LOW) {
        state = DEBOUNCING;
        delay(500); // debounce delay
        noTone(BUZZER); // Arrêter le son du buzzer après le délai
      }
      break;

    case DEBOUNCING:
      if (pirVal == LOW) {
        state = IDLE;
        score++; // Incrémente le score
        sevseg.setNumber(score);
        sevseg.refreshDisplay(); 
        digitalWrite(LED, LOW); // Éteindre la LED après l'incrément
      }
      break;
  }
}
