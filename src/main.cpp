#include <Arduino.h>
#include <Keypad.h>
#include "functions.h"

const int oneSec = 1000;
unsigned long prevSecTime = 0;
unsigned long totalSeconds = 0; // Change the number to set how many seconds it will countdown

byte stopStart = 0; // 0 = Pause |  1 = Start
byte setupMode = 0; // 0 = noSetup | 1 = setupMode

const byte ROW_NUM = 4;
const byte COLUMN_NUM = 4;

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
  char key = keypad.getKey();
  byte inputLoc;
  
  if (currentTime == 995)
  {
    digitalWrite(d1, HIGH);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, HIGH);
  }

  if (setupMode == 0)
  {
    timerDisplay(totalSeconds, inputLoc, setupMode);
  }

  // Timer decrement
  if (currentTime - prevSecTime >= oneSec &&  stopStart == 1){

    if (totalSeconds != 0) {
      totalSeconds--;
      Serial.print("Timer seconds check: ");
      Serial.println(totalSeconds);
    }

    prevSecTime += oneSec;
  }
  
  if (currentTime - prevSecTime >= oneSec) {
    Serial.print("Seconds check: ");
    Serial.println(totalSeconds);

    prevSecTime += oneSec;
  }

  if (key) {
    Serial.println(key);
  }


  // Stop and Start
  if (key == 'A' && stopStart == 0 && setupMode == 0) {
    stopStart = 1;
    prevSecTime = currentTime;
    Serial.println("Timer Start");
  } else if (key == 'A' && stopStart == 1 && setupMode == 0) {
    stopStart = 0;
    Serial.println("Timer pause");
  }

  if (key == 'C' && setupMode == 0) {
    setupMode = 1;
    stopStart = 0;
    Serial.println("Setup  on");
  } else if (key == 'C' && setupMode == 1) {
    setupMode = 0;
    stopStart = 0;
    prevSecTime = currentTime;
    Serial.println("Setup  off");
  }

  // Setup Mode
  if (setupMode == 1) {
    inputLoc = segInputLocation(key);
    totalSeconds = timerSetup(key, inputLoc);
    timerDisplay(totalSeconds, inputLoc, setupMode);
  }  
}