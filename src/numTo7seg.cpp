#include <Arduino.h>
#include "functions.h"

#define segE 12
#define segD 14
#define segC 27
#define segG 26
#define segA 25
#define segF 33
#define segB 32

void numTo7seg(byte seg7Num) {
  if (seg7Num == 9)
  {
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, LOW);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
  } else if (seg7Num == 8) {
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, LOW);
    digitalWrite(segE, LOW); 
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
  } else if (seg7Num == 7) {
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH); 
    digitalWrite(segF, HIGH);
    digitalWrite(segG, HIGH);
  } else if (seg7Num == 6) {
    digitalWrite(segA, LOW);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, LOW);
    digitalWrite(segD, LOW);
    digitalWrite(segE, LOW); 
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
  } else if (seg7Num == 5) {
    digitalWrite(segA, LOW);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, LOW);
    digitalWrite(segD, LOW);
    digitalWrite(segE, HIGH); 
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
  } else if (seg7Num == 4) {
    digitalWrite(segA, HIGH);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH); 
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
  } else if (seg7Num == 3) {
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, LOW);
    digitalWrite(segE, HIGH); 
    digitalWrite(segF, HIGH);
    digitalWrite(segG, LOW);
  }  else if (seg7Num == 2) {
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, LOW);
    digitalWrite(segE, LOW); 
    digitalWrite(segF, HIGH);
    digitalWrite(segG, LOW);
  } else if (seg7Num == 1) {
    digitalWrite(segA, HIGH);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH); 
    digitalWrite(segF, HIGH);
    digitalWrite(segG, HIGH);
  } else {
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, LOW);
    digitalWrite(segE, LOW); 
    digitalWrite(segF, LOW);
    digitalWrite(segG, HIGH);
  }
  
}