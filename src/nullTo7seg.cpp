#include <Arduino.h>
#include "functions.h"

#define inputHI HIGH
#define inputLO LOW

void nullTo7seg() {
  digitalWrite(segA, inputHI);
  digitalWrite(segB, inputHI);
  digitalWrite(segC, inputHI);
  digitalWrite(segD, inputHI);
  digitalWrite(segE, inputHI);
  digitalWrite(segF, inputHI);
  digitalWrite(segG, inputLO);
}