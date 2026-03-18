#include <Arduino.h>
#include "functions.h"

#define inputHI HIGH
#define inputLO LOW

void numTo7seg(byte seg7Num) {
  if (seg7Num == 9)
  {
    digitalWrite(segA, inputLO);
    digitalWrite(segB, inputLO);
    digitalWrite(segC, inputLO);
    digitalWrite(segD, inputLO);
    digitalWrite(segE, inputHI);
    digitalWrite(segF, inputLO);
    digitalWrite(segG, inputLO);
  } else if (seg7Num == 8) {
    digitalWrite(segA, inputLO);
    digitalWrite(segB, inputLO);
    digitalWrite(segC, inputLO);
    digitalWrite(segD, inputLO);
    digitalWrite(segE, inputLO); 
    digitalWrite(segF, inputLO);
    digitalWrite(segG, inputLO);
  } else if (seg7Num == 7) {
    digitalWrite(segA, inputLO);
    digitalWrite(segB, inputLO);
    digitalWrite(segC, inputLO);
    digitalWrite(segD, inputHI);
    digitalWrite(segE, inputHI); 
    digitalWrite(segF, inputHI);
    digitalWrite(segG, inputHI);
  } else if (seg7Num == 6) {
    digitalWrite(segA, inputLO);
    digitalWrite(segB, inputHI);
    digitalWrite(segC, inputLO);
    digitalWrite(segD, inputLO);
    digitalWrite(segE, inputLO); 
    digitalWrite(segF, inputLO);
    digitalWrite(segG, inputLO);
  } else if (seg7Num == 5) {
    digitalWrite(segA, inputLO);
    digitalWrite(segB, inputHI);
    digitalWrite(segC, inputLO);
    digitalWrite(segD, inputLO);
    digitalWrite(segE, inputHI); 
    digitalWrite(segF, inputLO);
    digitalWrite(segG, inputLO);
  } else if (seg7Num == 4) {
    digitalWrite(segA, inputHI);
    digitalWrite(segB, inputLO);
    digitalWrite(segC, inputLO);
    digitalWrite(segD, inputHI);
    digitalWrite(segE, inputHI); 
    digitalWrite(segF, inputLO);
    digitalWrite(segG, inputLO);
  } else if (seg7Num == 3) {
    digitalWrite(segA, inputLO);
    digitalWrite(segB, inputLO);
    digitalWrite(segC, inputLO);
    digitalWrite(segD, inputLO);
    digitalWrite(segE, inputHI); 
    digitalWrite(segF, inputHI);
    digitalWrite(segG, inputLO);
  }  else if (seg7Num == 2) {
    digitalWrite(segA, inputLO);
    digitalWrite(segB, inputLO);
    digitalWrite(segC, inputHI);
    digitalWrite(segD, inputLO);
    digitalWrite(segE, inputLO); 
    digitalWrite(segF, inputHI);
    digitalWrite(segG, inputLO);
  } else if (seg7Num == 1) {
    digitalWrite(segA, inputHI);
    digitalWrite(segB, inputLO);
    digitalWrite(segC, inputLO);
    digitalWrite(segD, inputHI);
    digitalWrite(segE, inputHI); 
    digitalWrite(segF, inputHI);
    digitalWrite(segG, inputHI);
  } else {
    digitalWrite(segA, inputLO);
    digitalWrite(segB, inputLO);
    digitalWrite(segC, inputLO);
    digitalWrite(segD, inputLO);
    digitalWrite(segE, inputLO); 
    digitalWrite(segF, inputLO);
    digitalWrite(segG, inputHI);
  }
  
}