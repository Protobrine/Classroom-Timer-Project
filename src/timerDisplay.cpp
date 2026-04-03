#include <Arduino.h>
#include "functions.h"

#define dHI HIGH
#define dLO LOW

const byte milliSec5 = 20; // You can set this to adjust the shift register clock
const int setupIndiInterval = 1000; // input indicator interval or blinking
const int delayFor7seg = 100; // delay for stability

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

byte displayFlicker = 0;

void timerDisplay(unsigned long timerSeconds, byte inputLocation, byte timerMode, unsigned long switchTime){
  unsigned long currentTime = millis();
  byte inputLoc = inputLocation; // 0-3 Hours and Mintues | 4-5 Minutes and Hours
  byte mode = timerMode; // 0 = setup off | 1 = setup on
  
  if (currentTime == delayFor7seg + switchTime) {
    prevMilliSecD4 = delayFor7seg + switchTime;
  }

  if (currentTime == seg7divide4 + delayFor7seg + switchTime) {
    prevMilliSecD3 = seg7divide4 + delayFor7seg + switchTime;
  }
  if (currentTime == seg7divide4*2 + delayFor7seg + switchTime) {
    prevMilliSecD2 = seg7divide4*2 + delayFor7seg + switchTime;
  }
  if (currentTime == seg7divide4*3 + delayFor7seg + switchTime) {
    prevMilliSecD1 = seg7divide4*3 + delayFor7seg + switchTime;
  }

  // Blinking 7 seg

  if (currentTime == setupIndiInterval/2 + delayFor7seg + switchTime) {
    prevMilliSetupD1 = setupIndiInterval/2 + delayFor7seg + switchTime;
  } 
  if (currentTime == setupIndiInterval + delayFor7seg + switchTime) {
    prevMilliSetupD2 = setupIndiInterval + delayFor7seg + switchTime;
  } 

  if (currentTime - prevMilliSetupD1 >= setupIndiInterval) {
    displayFlicker = 0;
    prevMilliSetupD1 += setupIndiInterval;
  }
  if (currentTime - prevMilliSetupD2 >= setupIndiInterval) {
    displayFlicker = 1;
    prevMilliSetupD2 += setupIndiInterval;
  }

  // Timer Countdown

  if (timerSeconds >= 3600 && mode == 0) { // Hours and Minutes
    
    if (currentTime - prevMilliSecD4 >= milliSec5){
      firstSecDigit = ((timerSeconds % 3600)/60) % 10;
      shiftRegister(firstSecDigit, 1);
      prevMilliSecD4 += milliSec5;
    }

    if (currentTime - prevMilliSecD3 >= milliSec5) {
      secondSecDigit = ((timerSeconds % 3600)/60) / 10;
      shiftRegister(secondSecDigit, 2);
      prevMilliSecD3 += milliSec5;
    }

    if (currentTime - prevMilliSecD2 >= milliSec5) {
      thirdSecDigit = (timerSeconds/3600) % 10;
      shiftRegister(thirdSecDigit, 3);
      prevMilliSecD2 += milliSec5;
    } 

    if (currentTime - prevMilliSecD1 >= milliSec5) {
      fourthSecDigit = (timerSeconds/3600) / 10;
      shiftRegister(fourthSecDigit, 4);
      prevMilliSecD1 += milliSec5;
    } 

  } else if (timerSeconds < 3600 && mode == 0) { // Minutes and Seconds
    
    if (currentTime - prevMilliSecD4 >= milliSec5){
      firstSecDigit = timerSeconds % 10;
      shiftRegister(firstSecDigit, 1);
      prevMilliSecD4 += milliSec5;
    }
    
    if (currentTime - prevMilliSecD3 >= milliSec5) {
        
      secondSecDigit = (timerSeconds % 60) / 10;
      shiftRegister(secondSecDigit, 2);
      prevMilliSecD3 += milliSec5;
    }

    if (currentTime - prevMilliSecD2 >= milliSec5) {
        
      thirdSecDigit = (timerSeconds/60) % 10;
      shiftRegister(thirdSecDigit, 3);
      prevMilliSecD2 += milliSec5;
    } 

    if (currentTime - prevMilliSecD1 >= milliSec5) {
        
      fourthSecDigit = (timerSeconds/60) / 10;
      shiftRegister(fourthSecDigit, 4);
      prevMilliSecD1 += milliSec5;
    } 
  }

  // SETUP MODE

  if (inputLoc <= 3 && mode == 1) { // Hours and Minutes
    
    if (currentTime - prevMilliSecD4 >= milliSec5){
      firstSecDigit = ((timerSeconds % 3600)/60) % 10;
      if (displayFlicker == 0 && inputLoc == 3) {
        shiftRegisterFlicker(1);
      } else if (displayFlicker == 1 && inputLoc == 3) {
        shiftRegister(firstSecDigit, 1);
      } else if (inputLoc != 3) {
        shiftRegister(firstSecDigit, 1);
      }
      prevMilliSecD4 += milliSec5;
    }

    if (currentTime - prevMilliSecD3 >= milliSec5) {
      secondSecDigit = ((timerSeconds % 3600)/60) / 10;
      if (displayFlicker == 0 && inputLoc == 2) {
        shiftRegisterFlicker(2);
      } else if (displayFlicker == 1 && inputLoc == 2) {
        shiftRegister(secondSecDigit, 2);
      } else if (inputLoc != 2) {
        shiftRegister(secondSecDigit, 2);
      }
      prevMilliSecD3 += milliSec5;
    }

    if (currentTime - prevMilliSecD2 >= milliSec5) {
      thirdSecDigit = (timerSeconds/3600) % 10;
      if (displayFlicker == 0 && inputLoc == 1) {
        shiftRegisterFlicker(3);
      } else if (displayFlicker == 1 && inputLoc == 1) {
        shiftRegister(thirdSecDigit, 3);
      } else if (inputLoc != 1) {
        shiftRegister(thirdSecDigit, 3);
      }
      prevMilliSecD2 += milliSec5;
    } 

    if (currentTime - prevMilliSecD1 >= milliSec5) {
      fourthSecDigit = (timerSeconds/3600) / 10;
      if (displayFlicker == 0 && inputLoc == 0) {
        shiftRegisterFlicker(4);
      } else if (displayFlicker == 1 && inputLoc == 0) {
        shiftRegister(fourthSecDigit, 4);
      } else if (inputLoc != 0) {
        shiftRegister(fourthSecDigit, 4);
      }
      prevMilliSecD1 += milliSec5;
    } 

  } else if (inputLoc > 3 && mode == 1) { // Minutes and Seconds
    
    if (currentTime - prevMilliSecD4 >= milliSec5){
      firstSecDigit = timerSeconds % 10;

      if (displayFlicker == 0 && inputLoc == 5) {
        shiftRegisterFlicker(1);
      } else if (displayFlicker == 1 && inputLoc == 5) {
        shiftRegister(firstSecDigit, 1);
      } else if (inputLoc != 5) {
        shiftRegister(firstSecDigit, 1);
      }
      prevMilliSecD4 += milliSec5;
    }
    
    if (currentTime - prevMilliSecD3 >= milliSec5) {
        
      secondSecDigit = (timerSeconds % 60) / 10;
      if (displayFlicker == 0 && inputLoc == 4) {
        shiftRegisterFlicker(2);
      } else if (displayFlicker == 1 && inputLoc == 4) {
        shiftRegister(secondSecDigit, 2);
      } else if (inputLoc != 4) {
        shiftRegister(secondSecDigit, 2);
      }
      prevMilliSecD3 += milliSec5;
    }

    if (currentTime - prevMilliSecD2 >= milliSec5) {
        
      thirdSecDigit = ((timerSeconds % 3600) / 60) % 10;
      shiftRegister(thirdSecDigit, 3);
      prevMilliSecD2 += milliSec5;
    } 

    if (currentTime - prevMilliSecD1 >= milliSec5) {
        
      fourthSecDigit = ((timerSeconds % 3600) / 60) / 10;
      shiftRegister(fourthSecDigit, 4);
      prevMilliSecD1 += milliSec5;
    } 
  }
}