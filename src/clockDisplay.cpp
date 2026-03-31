#include <Arduino.h>
#include "functions.h"

#define dHI HIGH
#define dLO LOW

const byte milliSecTime = 16; // You can set this to adjust the flicker
const int delayFor7segTime = 100; // delay for stability

unsigned long prevMilliSecTimeD4;
unsigned long prevMilliSecTimeD3;
unsigned long prevMilliSecTimeD2;
unsigned long prevMilliSecTimeD1;

byte seg7divide4Time = milliSecTime/4;

byte firstSecDigitTime = 0;
byte secondSecDigitTime = 0;
byte thirdSecDigitTime = 0;
byte fourthSecDigitTime = 0;

void clockDisplay(unsigned long clockSeconds, unsigned long switchTime, byte clockState){
  unsigned long currentTime = millis();
  
  if (currentTime == delayFor7segTime + switchTime) {
    prevMilliSecTimeD4 = delayFor7segTime + switchTime;
  }

  if (currentTime == seg7divide4Time + delayFor7segTime + switchTime) {
    prevMilliSecTimeD3 = seg7divide4Time + delayFor7segTime + switchTime;
  }
  if (currentTime == seg7divide4Time*2 + delayFor7segTime + switchTime) {
    prevMilliSecTimeD2 = seg7divide4Time*2 + delayFor7segTime + switchTime;
  }
  if (currentTime == seg7divide4Time*3 + delayFor7segTime + switchTime) {
    prevMilliSecTimeD1 = seg7divide4Time*3 + delayFor7segTime + switchTime;
  }

  // Clock | Well look at the time
  
  if (clockState == 0){
    if (currentTime - prevMilliSecTimeD4 >= milliSecTime){
      firstSecDigitTime = ((clockSeconds % 3600)/60) % 10;
      shiftRegister(firstSecDigitTime, 1);
      prevMilliSecTimeD4 += milliSecTime;
    }

    if (currentTime - prevMilliSecTimeD3 >= milliSecTime) {
      secondSecDigitTime = ((clockSeconds % 3600)/60) / 10;
      shiftRegister(secondSecDigitTime, 2);
      prevMilliSecTimeD3 += milliSecTime;
    }

    if (currentTime - prevMilliSecTimeD2 >= milliSecTime) {
      thirdSecDigitTime = (clockSeconds/3600) % 10;
      shiftRegister(thirdSecDigitTime, 3);
      prevMilliSecTimeD2 += milliSecTime;
    } 

    if (currentTime - prevMilliSecTimeD1 >= milliSecTime) {
      fourthSecDigitTime = (clockSeconds/3600) / 10;
      shiftRegister(fourthSecDigitTime, 4);
      prevMilliSecTimeD1 += milliSecTime;
    }
  } else if (clockState == 1) {
    if (currentTime - prevMilliSecTimeD4 >= milliSecTime){
      clockNullRegister(1);
      prevMilliSecTimeD4 += milliSecTime;
    }

    if (currentTime - prevMilliSecTimeD3 >= milliSecTime) {
      clockNullRegister(2);
      prevMilliSecTimeD3 += milliSecTime;
    }

    if (currentTime - prevMilliSecTimeD2 >= milliSecTime) {
      clockNullRegister(3);
      prevMilliSecTimeD2 += milliSecTime;
    } 

    if (currentTime - prevMilliSecTimeD1 >= milliSecTime) {
      clockNullRegister(4);
      prevMilliSecTimeD1 += milliSecTime;
    }
  }
}