#include <Arduino.h>
#include "functions.h"

const byte milliSec5 = 20; // You can set this to adjust the flicker
const int delayFor7seg = 1000; // delay for stability
unsigned long prevMilliSecD4;
unsigned long prevMilliSecD3;
unsigned long prevMilliSecD2;
unsigned long prevMilliSecD1;

byte seg7divide4 = milliSec5/4;

byte firstSecDigit = 0;
byte secondSecDigit = 0;
byte thirdSecDigit = 0;
byte fourthSecDigit = 0;

void timerDisplay(unsigned long timerSeconds){
  unsigned long currentTime = millis();


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

  if (timerSeconds >= 3600) {

    if (currentTime - prevMilliSecD4 >= milliSec5){
    firstSecDigit = ((timerSeconds % 3600)/60) % 10;
    numTo7seg(firstSecDigit);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(d3, LOW);
    digitalWrite(d4, HIGH);
    prevMilliSecD4 = currentTime;
    }

    if (currentTime - prevMilliSecD3 >= milliSec5) {
      secondSecDigit = ((timerSeconds % 3600)/60) / 10;
      numTo7seg(secondSecDigit);
      digitalWrite(d1, LOW);
      digitalWrite(d2, LOW);
      digitalWrite(d3, HIGH);
      digitalWrite(d4, LOW);
      prevMilliSecD3 = currentTime;
    }

    if (currentTime - prevMilliSecD2 >= milliSec5) {
      thirdSecDigit = (timerSeconds/3600) % 10;
      numTo7seg(thirdSecDigit);
      digitalWrite(d1, LOW);
      digitalWrite(d2, HIGH);
      digitalWrite(d3, LOW);
      digitalWrite(d4, LOW);
      prevMilliSecD2 += milliSec5;
    } 

    if (currentTime - prevMilliSecD1 >= milliSec5) {
      fourthSecDigit = (timerSeconds/3600) / 10;
      numTo7seg(fourthSecDigit);
      digitalWrite(d1, HIGH);
      digitalWrite(d2, LOW);
      digitalWrite(d3, LOW);
      digitalWrite(d4, LOW);
      prevMilliSecD1 += milliSec5;
    } 

  } else {
    
    if (currentTime - prevMilliSecD4 >= milliSec5){
      firstSecDigit = timerSeconds % 10;
      numTo7seg(firstSecDigit);
      digitalWrite(d1, LOW);
      digitalWrite(d2, LOW);
      digitalWrite(d3, LOW);
      digitalWrite(d4, HIGH);
      prevMilliSecD4 = currentTime;
    }
    
    if (currentTime - prevMilliSecD3 >= milliSec5) {
        
      secondSecDigit = (timerSeconds % 60) / 10;
      numTo7seg(secondSecDigit);
      digitalWrite(d1, LOW);
      digitalWrite(d2, LOW);
      digitalWrite(d3, HIGH);
      digitalWrite(d4, LOW);
    prevMilliSecD3 = currentTime;
    }

    if (currentTime - prevMilliSecD2 >= milliSec5) {
        
      thirdSecDigit = (timerSeconds/60) % 10;
      numTo7seg(thirdSecDigit);
      digitalWrite(d1, LOW);
      digitalWrite(d2, HIGH);
      digitalWrite(d3, LOW);
      digitalWrite(d4, LOW);
      prevMilliSecD2 += milliSec5;
    } 

    if (currentTime - prevMilliSecD1 >= milliSec5) {
        
      fourthSecDigit = (timerSeconds/60) / 10;
      numTo7seg(fourthSecDigit);
      digitalWrite(d1, HIGH);
      digitalWrite(d2, LOW);
      digitalWrite(d3, LOW);
      digitalWrite(d4, LOW);
      prevMilliSecD1 += milliSec5;
    } 
  }
}