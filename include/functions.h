#include <Arduino.h>

#ifndef functions_h
#define functions_h

#define extendPin 23 // 23 || 13
#define STCP 22      // 22 || 14
#define SHCP 21      // 21 || 27
#define DS1 19       // 19 || 12
#define DS2 18       // 18 || 26
#define DS3 17       // 17 || 25
#define DS4 16       // 16 || 33

#define buzzer 4    // 4 || 32

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
unsigned long timerSetup(char setupKey, byte inputLocation, byte reset);

#endif