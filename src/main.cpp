#include <Arduino.h>
#include <Keypad.h>
#include "functions.h"

const int oneSec = 1000;
unsigned long prevSecTime = 0;
unsigned long totalSeconds = 3610; // Change the number to set how many seconds it will countdown

const byte ROW_NUM = 4; //four rows
const byte COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM]      = {22,21,19,18};
byte pin_column[COLUMN_NUM] = {5,17,16,4};

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup() {
  Serial.begin(9600);

  pinMode(segE, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(segA, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d1, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime == 995)
  {
    digitalWrite(d1, HIGH);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, HIGH);
  }

  timerDisplay(totalSeconds);

  if (currentTime - prevSecTime >= oneSec){

    if (totalSeconds != 0) {
      totalSeconds--;
    }

    prevSecTime += oneSec;
  }

  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
  }
  
}