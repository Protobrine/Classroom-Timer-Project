#include <Arduino.h>
#include "functions.h"

int nullInput [1][8]{
  {0,0,0,0,0,0,0,1}
//A,B,C,D,E,F,G
};

// The line that will display if there is no wifi
void clockNullRegister(byte position) {
  if (position == 1) {
    shiftReExtend(1);
    for (int i = 7; i>= 0; i--) {
      shiftReExtend(2);
      if (nullInput[0][i]==0){
        digitalWrite(DS1, LOW);
      } 
      if (nullInput[0][i]==1){
        digitalWrite(DS1, HIGH);
      } 
      shiftReExtend(1);
    }
    shiftReExtend(0);
  } else if (position == 2) {
    shiftReExtend(4);
    for (int i = 7; i>= 0; i--) {
      shiftReExtend(5);
      if (nullInput[0][i]==0){
        digitalWrite(DS2, LOW);
      } 
      if (nullInput[0][i]==1){
        digitalWrite(DS2, HIGH);
      } 
      shiftReExtend(4);
    }
    shiftReExtend(3);
  } else if (position == 3) {
    shiftReExtend(7);;
    for (int i = 7; i>= 0; i--) {
      shiftReExtend(8);
      if (nullInput[0][i]==0){
        digitalWrite(DS3, LOW);
      } 
      if (nullInput[0][i]==1){
        digitalWrite(DS3, HIGH);
      } 
      shiftReExtend(7);
    }
    shiftReExtend(6);
  } else if (position == 4) {
    shiftReExtend(10);
    for (int i = 7; i>= 0; i--) {
      shiftReExtend(11);
      if (nullInput[0][i]==0){
        digitalWrite(DS4, LOW);
      } 
      if (nullInput[0][i]==1){
        digitalWrite(DS4, HIGH);
      } 
      shiftReExtend(10);
    }
    shiftReExtend(9);
  }
}