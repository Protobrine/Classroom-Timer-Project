#include <Arduino.h>

#ifndef functions_h
#define functions_h

#define segE 12
#define segD 14
#define segC 27
#define segG 26
#define segA 25
#define segF 33
#define segB 32
#define d4 15
#define d3 2
#define d2 0
#define d1 13

void numTo7seg(byte seg7Num);
void timerDisplay(unsigned long timerSeconds);

#endif