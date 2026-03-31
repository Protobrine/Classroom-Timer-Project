#include <Arduino.h>
#include "functions.h"

int extendPosition [12][8] {
  {1,1,1,1,1,1,1,1}, // Pos 1
  {0,1,1,1,1,1,1,1},
  {0,0,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1}, // Pos 2
  {1,1,0,1,1,1,1,1},
  {1,1,0,0,1,1,1,1},
  {1,1,1,1,1,1,1,1}, // Pos 3
  {1,1,1,1,0,1,1,1},
  {1,1,1,1,0,0,1,1},
  {1,1,1,1,1,1,1,1}, // Pos 4
  {1,1,1,1,1,1,0,1},
  {1,1,1,1,1,1,0,0}
};

void shiftReExtend(int position) {
  digitalWrite(STCP, LOW);
  for (int i = 7; i>= 0; i--) {
    digitalWrite(SHCP, LOW);
    if (extendPosition[position][i]==0){
      digitalWrite(extendPin, LOW);
    } 
    if (extendPosition[position][i]==1){
      digitalWrite(extendPin, HIGH);
    } 
    digitalWrite(SHCP, HIGH);
  }
  digitalWrite(STCP, HIGH);
}