#include <Arduino.h>
#include "functions.h"

const int oneSec = 1000;
unsigned long prevSecTime = 0;

unsigned long totalSeconds = 3610; // Change the number to set how many seconds it will countdown

void setup() {
  Serial.begin(9600);

  pinMode(segE, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(segA, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d1, OUTPUT);
}



void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime == 995)
  {
    digitalWrite(d1, HIGH);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, HIGH);
  }

  timerDisplay(totalSeconds);

  if (currentTime - prevSecTime >= oneSec){

    if (totalSeconds != 0) {
      totalSeconds--;
    }

    prevSecTime += oneSec;
  }

}