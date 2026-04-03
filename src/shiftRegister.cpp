#include <Arduino.h>
#include "functions.h"

// Translation of digit to the block display
int digits [10][8]{
  {0,1,1,1,1,1,1,0}, // digit 0
  {0,0,1,1,0,0,0,0}, // digit 1
  {0,1,1,0,1,1,0,1}, // digit 2
  {0,1,1,1,1,0,0,1}, // digit 3
  {0,0,1,1,0,0,1,1}, // digit 4
  {0,1,0,1,1,0,1,1}, // digit 5
  {0,1,0,1,1,1,1,1}, // digit 6
  {0,1,1,1,0,0,0,0}, // digit 7
  {0,1,1,1,1,1,1,1}, // digit 8
  {0,1,1,1,1,0,1,1}, // digit 9
//A,B,C,D,E,F,G
};

void shiftRegister(byte Digit, byte position) {
  if (position == 1) {
    shiftReExtend(1);
    for (int i = 7; i>= 0; i--) {
      shiftReExtend(2);
      if (digits[Digit][i]==0){
        digitalWrite(DS1, LOW);
      } 
      if (digits[Digit][i]==1){
        digitalWrite(DS1, HIGH);
      } 
      shiftReExtend(1);
    }
    shiftReExtend(0);
  } else if (position == 2) {
    shiftReExtend(4);
    for (int i = 7; i>= 0; i--) {
      shiftReExtend(5);
      if (digits[Digit][i]==0){
        digitalWrite(DS2, LOW);
      } 
      if (digits[Digit][i]==1){
        digitalWrite(DS2, HIGH);
      } 
      shiftReExtend(4);
    }
    shiftReExtend(3);
  } else if (position == 3) {
    shiftReExtend(7);;
    for (int i = 7; i>= 0; i--) {
      shiftReExtend(8);
      if (digits[Digit][i]==0){
        digitalWrite(DS3, LOW);
      } 
      if (digits[Digit][i]==1){
        digitalWrite(DS3, HIGH);
      } 
      shiftReExtend(7);
    }
    shiftReExtend(6);
  } else if (position == 4) {
    shiftReExtend(10);
    for (int i = 7; i>= 0; i--) {
      shiftReExtend(11);
      if (digits[Digit][i]==0){
        digitalWrite(DS4, LOW);
      } 
      if (digits[Digit][i]==1){
        digitalWrite(DS4, HIGH);
      } 
      shiftReExtend(10);
    }
    shiftReExtend(9);
  }
}