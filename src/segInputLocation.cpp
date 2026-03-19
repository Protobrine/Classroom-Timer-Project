#include <Arduino.h>
#include "functions.h"

byte segLocation = 0;

byte segInputLocation(char setupKey) {
  
  if (setupKey == 'C') {
    segLocation = 0;
  }
  if (setupKey == '*') {
      if (segLocation > 0) {
        segLocation--;
        Serial.print("Backward: ");
        Serial.println(segLocation);
      }
    }
  if (setupKey == '#') {
    if (segLocation < 5) {
      segLocation++;
      Serial.print("Forward: ");
      Serial.println(segLocation);
    }
  }

  return segLocation;
}