#include <Arduino.h>
#include "functions.h"

#define dHI HIGH
#define dLO LOW

const byte milliSec5 = 20; // You can set this to adjust the flicker
const int setupIndiInterval = 2000; // input indicator interval
const int delayFor7seg = 1000; // delay for stability

unsigned long prevMilliSecD4;
unsigned long prevMilliSecD3;
unsigned long prevMilliSecD2;
unsigned long prevMilliSecD1;

unsigned long prevMilliSetupD1;
unsigned long prevMilliSetupD2;

byte seg7divide4 = milliSec5/4;

byte firstSecDigit = 0;
byte secondSecDigit = 0;
byte thirdSecDigit = 0;
byte fourthSecDigit = 0;

void timerDisplay(unsigned long timerSeconds, byte inputLocation, byte timerMode){
  unsigned long currentTime = millis();
  byte inputLoc = inputLocation; // 0-3 Hours and Mintues | 4-5 Minutes and Hours
  byte mode = timerMode; // 0 = setup off | 1 = setup on
  byte displayFlicker;
  
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

  // Blinking 7 seg

  if (currentTime == delayFor7seg) {
    displayFlicker = 0;
    prevMilliSetupD1 = delayFor7seg;
  } 
  if (currentTime == delayFor7seg + delayFor7seg) {
    prevMilliSetupD2 = delayFor7seg + delayFor7seg;
  } 

  if (currentTime - prevMilliSetupD1 >= setupIndiInterval) {
    prevMilliSetupD1 += setupIndiInterval;
  }
  if (currentTime - prevMilliSetupD2 >= setupIndiInterval) {
    prevMilliSetupD2 += setupIndiInterval;
  }

  // Timer Countdown

  if (timerSeconds >= 3600 && mode == 0) { // Hours and Minutes
    
    if (currentTime - prevMilliSecD4 >= milliSec5){
      firstSecDigit = ((timerSeconds % 3600)/60) % 10;
      numTo7seg(firstSecDigit);
      digitalWrite(d1, dLO);
      digitalWrite(d2, dLO);
      digitalWrite(d3, dLO);
      digitalWrite(d4, dHI);
      prevMilliSecD4 += milliSec5;
    }

    if (currentTime - prevMilliSecD3 >= milliSec5) {
      secondSecDigit = ((timerSeconds % 3600)/60) / 10;
      numTo7seg(secondSecDigit);
      digitalWrite(d1, dLO);
      digitalWrite(d2, dLO);
      digitalWrite(d3, dHI);
      digitalWrite(d4, dLO);
      prevMilliSecD3 += milliSec5;
    }

    if (currentTime - prevMilliSecD2 >= milliSec5) {
      thirdSecDigit = (timerSeconds/3600) % 10;
      numTo7seg(thirdSecDigit);
      digitalWrite(d1, dLO);
      digitalWrite(d2, dHI);
      digitalWrite(d3, dLO);
      digitalWrite(d4, dLO);
      prevMilliSecD2 += milliSec5;
    } 

    if (currentTime - prevMilliSecD1 >= milliSec5) {
      fourthSecDigit = (timerSeconds/3600) / 10;
      numTo7seg(fourthSecDigit);
      digitalWrite(d1, dHI);
      digitalWrite(d2, dLO);
      digitalWrite(d3, dLO);
      digitalWrite(d4, dLO);
      prevMilliSecD1 += milliSec5;
    } 

  } else if (timerSeconds < 3600 && mode == 0) { // Minutes and Seconds
    
    if (currentTime - prevMilliSecD4 >= milliSec5){
      firstSecDigit = timerSeconds % 10;
      numTo7seg(firstSecDigit);
      digitalWrite(d1, dLO);
      digitalWrite(d2, dLO);
      digitalWrite(d3, dLO);
      digitalWrite(d4, dHI);
      prevMilliSecD4 += milliSec5;
    }
    
    if (currentTime - prevMilliSecD3 >= milliSec5) {
        
      secondSecDigit = (timerSeconds % 60) / 10;
      numTo7seg(secondSecDigit);
      digitalWrite(d1, dLO);
      digitalWrite(d2, dLO);
      digitalWrite(d3, dHI);
      digitalWrite(d4, dLO);
      prevMilliSecD3 += milliSec5;
    }

    if (currentTime - prevMilliSecD2 >= milliSec5) {
        
      thirdSecDigit = (timerSeconds/60) % 10;
      numTo7seg(thirdSecDigit);
      digitalWrite(d1, dLO);
      digitalWrite(d2, dHI);
      digitalWrite(d3, dLO);
      digitalWrite(d4, dLO);
      prevMilliSecD2 += milliSec5;
    } 

    if (currentTime - prevMilliSecD1 >= milliSec5) {
        
      fourthSecDigit = (timerSeconds/60) / 10;
      numTo7seg(fourthSecDigit);
      digitalWrite(d1, dHI);
      digitalWrite(d2, dLO);
      digitalWrite(d3, dLO);
      digitalWrite(d4, dLO);
      prevMilliSecD1 += milliSec5;
    } 
  }

  // SETUP MODE

  if (inputLoc <= 3 && mode == 1) { // Hours and Minutes
    
    if (currentTime - prevMilliSecD4 >= milliSec5){
      firstSecDigit = ((timerSeconds % 3600)/60) % 10;
      numTo7seg(firstSecDigit);
      digitalWrite(d1, dLO);
      digitalWrite(d2, dLO);
      digitalWrite(d3, dLO);
      digitalWrite(d4, dHI);
      prevMilliSecD4 += milliSec5;
    }

    if (currentTime - prevMilliSecD3 >= milliSec5) {
      secondSecDigit = ((timerSeconds % 3600)/60) / 10;
      numTo7seg(secondSecDigit);
      digitalWrite(d1, dLO);
      digitalWrite(d2, dLO);
      digitalWrite(d3, dHI);
      digitalWrite(d4, dLO);
      prevMilliSecD3 += milliSec5;
    }

    if (currentTime - prevMilliSecD2 >= milliSec5) {
      thirdSecDigit = (timerSeconds/3600) % 10;
      numTo7seg(thirdSecDigit);
      digitalWrite(d1, dLO);
      digitalWrite(d2, dHI);
      digitalWrite(d3, dLO);
      digitalWrite(d4, dLO);
      prevMilliSecD2 += milliSec5;
    } 

    if (currentTime - prevMilliSecD1 >= milliSec5) {
      fourthSecDigit = (timerSeconds/3600) / 10;
      numTo7seg(fourthSecDigit);

      if (displayFlicker == 0) {
        digitalWrite(d1, dHI);
        digitalWrite(d2, dLO);
        digitalWrite(d3, dLO);
        digitalWrite(d4, dLO);
      }
      

      
      prevMilliSecD1 += milliSec5;
    } 

  } else if (inputLoc > 3 && mode == 1) { // Minutes and Seconds
    
    if (currentTime - prevMilliSecD4 >= milliSec5){
      firstSecDigit = timerSeconds % 10;
      numTo7seg(firstSecDigit);
      digitalWrite(d1, dLO);
      digitalWrite(d2, dLO);
      digitalWrite(d3, dLO);
      digitalWrite(d4, dHI);
      prevMilliSecD4 += milliSec5;
    }
    
    if (currentTime - prevMilliSecD3 >= milliSec5) {
        
      secondSecDigit = (timerSeconds % 60) / 10;
      numTo7seg(secondSecDigit);
      digitalWrite(d1, dLO);
      digitalWrite(d2, dLO);
      digitalWrite(d3, dHI);
      digitalWrite(d4, dLO);
      prevMilliSecD3 += milliSec5;
    }

    if (currentTime - prevMilliSecD2 >= milliSec5) {
        
      thirdSecDigit = ((timerSeconds % 3600) / 60) % 10;
      numTo7seg(thirdSecDigit);
      digitalWrite(d1, dLO);
      digitalWrite(d2, dHI);
      digitalWrite(d3, dLO);
      digitalWrite(d4, dLO);
      prevMilliSecD2 += milliSec5;
    } 

    if (currentTime - prevMilliSecD1 >= milliSec5) {
        
      fourthSecDigit = ((timerSeconds % 3600) / 60) / 10;
      numTo7seg(fourthSecDigit);
      digitalWrite(d1, dHI);
      digitalWrite(d2, dLO);
      digitalWrite(d3, dLO);
      digitalWrite(d4, dLO);
      prevMilliSecD1 += milliSec5;
    } 
  }
}