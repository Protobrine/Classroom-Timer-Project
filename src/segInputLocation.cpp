#include <Arduino.h>
#include "functions.h"

byte segLocation = 0; // Location of number in setup mode 0-5
byte incrementThing = 0; // When the number is pressed go to next number

byte segInputLocation(char setupKey, byte incrementer) {
  incrementThing = incrementer;
  if (setupKey == 'C') {
    segLocation = 0;
  }
  if (setupKey == '*') {
      if (segLocation > 0) {
        segLocation--;
        Serial.print("Backward: ");
        Serial.println(segLocation);
      } else {
        segLocation = 5;
      }
    }
  if (setupKey == '#') {
    if (segLocation < 5) {
      segLocation++;
      Serial.print("Forward: ");
      Serial.println(segLocation);
    } else {
      segLocation = 0;
    }
  }
  if (incrementThing == 1) {
    segLocation++;
    incrementThing = 0;
  }
  
  return segLocation;
}