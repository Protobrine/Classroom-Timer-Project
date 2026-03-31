#include <Arduino.h>
#include "functions.h"

int digitsFlicker [1][8]{
  {0,0,0,0,0,0,0,0}
//A,B,C,D,E,F,G
};

void shiftRegisterFlicker(byte position) {
  if (position == 1) {
    shiftReExtend(1);
    for (int i = 7; i>= 0; i--) {
      shiftReExtend(2);
      if (digitsFlicker[0][i]==0){
        digitalWrite(DS1, LOW);
      } 
      if (digitsFlicker[0][i]==1){
        digitalWrite(DS1, HIGH);
      } 
      shiftReExtend(1);
    }
    shiftReExtend(0);
  } else if (position == 2) {
    shiftReExtend(4);
    for (int i = 7; i>= 0; i--) {
      shiftReExtend(5);
      if (digitsFlicker[0][i]==0){
        digitalWrite(DS2, LOW);
      } 
      if (digitsFlicker[0][i]==1){
        digitalWrite(DS2, HIGH);
      } 
      shiftReExtend(4);
    }
    shiftReExtend(3);
  } else if (position == 3) {
    shiftReExtend(7);;
    for (int i = 7; i>= 0; i--) {
      shiftReExtend(8);
      if (digitsFlicker[0][i]==0){
        digitalWrite(DS3, LOW);
      } 
      if (digitsFlicker[0][i]==1){
        digitalWrite(DS3, HIGH);
      } 
      shiftReExtend(7);
    }
    shiftReExtend(6);
  } else if (position == 4) {
    shiftReExtend(10);
    for (int i = 7; i>= 0; i--) {
      shiftReExtend(11);
      if (digitsFlicker[0][i]==0){
        digitalWrite(DS4, LOW);
      } 
      if (digitsFlicker[0][i]==1){
        digitalWrite(DS4, HIGH);
      } 
      shiftReExtend(10);
    }
    shiftReExtend(9);
  }
}