#include <Arduino.h>
#include <Keypad.h>
#include "functions.h"

const int oneSec = 1000;
unsigned long prevSecTime = 0;
unsigned long totalSeconds = 3600; // Change the number to set how many seconds it will countdown

byte stopStart = 1; // 0 = Pause |  1 = Start
byte setupMode = 0; // 0 = noSetup | 1 = setupMode
byte timerInput[6] =  {0,0,0,0,0,0}; // {hr1, hr2, min1, min2, sec1, sec2}
byte inputLoc = 0;

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

  Serial.println(timerInput[4]);
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

  if (currentTime - prevSecTime >= oneSec &&  stopStart == 1){

    if (totalSeconds != 0) {
      totalSeconds--;
      timerInput[0] = (totalSeconds/3600) / 10;
      timerInput[1] = (totalSeconds/3600) % 10;
      timerInput[2] = ((totalSeconds % 3600)/60) / 10;
      timerInput[3] = ((totalSeconds % 3600)/60) % 10;
      timerInput[4] = (totalSeconds % 60) / 10;
      timerInput[5] = totalSeconds % 10;
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

  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
  }

  if (key == 'A' && stopStart == 0 && setupMode == 0) {
    stopStart = 1;
    prevSecTime = currentTime;
    Serial.println("Timer Start");
  } else if (key == 'A' && stopStart == 1 && setupMode == 0) {
    stopStart = 0;
    Serial.println("Timer pause");
  }

// * = back, # = forward, but inputs first

// Setup Mode C
  if (key == 'C' && setupMode == 0) {
    setupMode = 1;
    stopStart = 0;
    inputLoc = 0;
    Serial.println("Setup  on");
  } else if (key == 'C' && setupMode == 1) {
    setupMode = 0;
    stopStart = 1;
    prevSecTime = currentTime;
    Serial.println("Setup  off");
  }

  if (setupMode == 1) {
    if (key == '*') {
      if (inputLoc > 0) {
        inputLoc--;
        Serial.print("Backward: ");
        Serial.println(inputLoc);
      }
    }
    if (key == '#') {
      if (inputLoc < 5) {
        inputLoc++;
        Serial.print("Forward: ");
        Serial.println(inputLoc);
      }
    }
    if (key == 'B') {
      Serial.println("RESET");
      timerInput[0] = 0;
      timerInput[1] = 0;
      timerInput[2] = 0;
      timerInput[3] = 0;
      timerInput[4] = 0;
      timerInput[5] = 0;
    }

    if (keypadNumConvert(key) <= 9)
    {
      if (inputLoc == 2 || inputLoc == 4) {
        if (keypadNumConvert(key) <= 5) {
          timerInput[inputLoc] = keypadNumConvert(key);
          Serial.print("Number Input: ");
          Serial.println(keypadNumConvert(key));
        } else {
          Serial.println("Time error");
        }
      } else if (inputLoc == 0) {
        if (keypadNumConvert(key) <= 2) {
          timerInput[inputLoc] = keypadNumConvert(key);
          Serial.print("Number Input: ");
          Serial.println(keypadNumConvert(key));
        } else {
          Serial.println("Time error");
        }
      } else if (inputLoc == 1) {
        if (timerInput[0] == 2) {
          if (keypadNumConvert(key) <= 4) {
            timerInput[inputLoc] = keypadNumConvert(key);
            Serial.print("Number Input: ");
            Serial.println(keypadNumConvert(key));
          } else if (timerInput[0] != 2) {
            timerInput[inputLoc] = keypadNumConvert(key);
            Serial.print("Number Input: ");
            Serial.println(keypadNumConvert(key));
          } else {
            Serial.println("Time error");
          }
          
        }
      } else if (inputLoc == 3 || inputLoc == 5) {
        timerInput[inputLoc] = keypadNumConvert(key);
        Serial.print("Number Input: ");
        Serial.println(keypadNumConvert(key));
      } else {
        Serial.println("Time error");
      }

    }

    totalSeconds = (timerInput[0]*3600*10) + (timerInput[1]*3600) + (timerInput[2]*60*10) + (timerInput[3]*60) + 
    (timerInput[4]*10) + (timerInput[5]);
  }  

}