#include <Arduino.h>
#include "functions.h"

#define segE 12
#define segD 14
#define segC 27
#define segG 26
#define segA 25
#define segF 33
#define segB 32
#define d4 15
#define d3 4
#define d2 0
#define d1 2

const int oneSec = 1000;
const long milliSec5 = 20; // You can set this to adjust the flicker
const long delayFor7seg = 1000; // delay for stability
unsigned long prevSecTime = 0;
unsigned long prevMilliSecD4;
unsigned long prevMilliSecD3;
unsigned long prevMilliSecD2;
unsigned long prevMilliSecD1;
unsigned long totalSeconds = 80; // Change the number to set how many seconds it will countdown

unsigned long seg7divide4 = milliSec5/4;

byte firstSecDigit = 0;
byte secondSecDigit = 0;
byte thirdSecDigit = 0;
byte fourthSecDigit = 0;

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

  if (currentTime == delayFor7seg) {
    prevMilliSecD3 = delayFor7seg;
  }

  if (currentTime == seg7divide4 + delayFor7seg) {
    prevMilliSecD3 = seg7divide4 + delayFor7seg;
  }
  if (currentTime == seg7divide4*2 + delayFor7seg) {
    prevMilliSecD2 = seg7divide4*2 + delayFor7seg;
  }
  if (currentTime == seg7divide4*3 + delayFor7seg) {
    prevMilliSecD1 = seg7divide4*3 + delayFor7seg;
  }

  if (currentTime - prevMilliSecD4 >= milliSec5){
    firstSecDigit = totalSeconds % 10;
    numTo7seg(firstSecDigit);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(d3, LOW);
    digitalWrite(d4, HIGH);
    prevMilliSecD4 = currentTime;
  }
  
  if (currentTime - prevMilliSecD3 >= milliSec5) {
    
    secondSecDigit = (totalSeconds%60)/10;
    numTo7seg(secondSecDigit);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, LOW);
    prevMilliSecD3 = currentTime;
  }

  if (currentTime - prevMilliSecD2 >= milliSec5) {
    
    numTo7seg(thirdSecDigit);
    digitalWrite(d1, LOW);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, LOW);
    digitalWrite(d4, LOW);
    prevMilliSecD2 += milliSec5;
  } 

  if (currentTime - prevMilliSecD1 >= milliSec5) {
    
    numTo7seg(fourthSecDigit);
    digitalWrite(d1, HIGH);
    digitalWrite(d2, LOW);
    digitalWrite(d3, LOW);
    digitalWrite(d4, LOW);
    prevMilliSecD1 += milliSec5;
  } 

  if (currentTime - prevSecTime >= oneSec){

    if (totalSeconds != 0) {
      totalSeconds--;
    }

    prevSecTime += oneSec;
  }

}