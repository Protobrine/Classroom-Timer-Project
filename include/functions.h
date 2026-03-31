#include <Arduino.h>

#ifndef functions_h
#define functions_h

#define extendPin 13
#define STCP 14
#define SHCP 27
#define DS1 12
#define DS2 26
#define DS3 25
#define DS4 33

#define buzzer 32

void shiftRegister(byte Digit, byte position);
void shiftRegisterFlicker(byte position);
void shiftReExtend(int position);
void clockNullRegister(byte position);
void ringBuzzer(unsigned long buzzTotalSeconds);
void timerDisplay(unsigned long timerSeconds, byte inputLocation, byte timerMode, unsigned long switchTime);
void clockDisplay(unsigned long clockSeconds, unsigned long switchTime, byte clockState);
unsigned long getTotalSecTime();
byte keypadNumConvert(char keyInput);
byte segInputLocation(char setupKey, byte incrementer);
unsigned long timerSetup(char setupKey, byte inputLocation);

#endif