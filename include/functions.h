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

#define buzzer 23

void numTo7seg(byte seg7Num);
void nullTo7seg();
void ringBuzzer(unsigned long buzzTotalSeconds);
void timerDisplay(unsigned long timerSeconds, byte inputLocation, byte timerMode, unsigned long switchTime);
void clockDisplay(unsigned long clockSeconds, unsigned long switchTime, byte clockState);
unsigned long getTotalSecTime();
byte keypadNumConvert(char keyInput);
byte segInputLocation(char setupKey);
unsigned long timerSetup(char setupKey, byte inputLocation);


#endif