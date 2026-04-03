#include <Arduino.h>
#include "functions.h"

// Conversion of input to seconds for the timer
byte timerInputSetup[6] =  {0,0,0,0,0,0};
unsigned long totalSecondsSetup;

unsigned long timerSetup(char setupKey, byte inputLocation, byte reset) {
  byte inputLoc = inputLocation;

  if (setupKey == 'B' && reset == 1) {
    Serial.println("RESET");
    timerInputSetup[0] = 0;
    timerInputSetup[1] = 0;
    timerInputSetup[2] = 0;
    timerInputSetup[3] = 0;
    timerInputSetup[4] = 0;
    timerInputSetup[5] = 0;
  }

  if (keypadNumConvert(setupKey) <= 9) {
    if (inputLoc == 2 || inputLoc == 4) {
      if (keypadNumConvert(setupKey) <= 5) {
        timerInputSetup[inputLoc] = keypadNumConvert(setupKey);
        Serial.print("Number Input: ");
        Serial.println(keypadNumConvert(setupKey));
      } else {
        Serial.println("Time error");
      }
    } else if (inputLoc == 0 || inputLoc == 1 || inputLoc == 3 || inputLoc == 5) {
      timerInputSetup[inputLoc] = keypadNumConvert(setupKey);
      Serial.print("Number Input: ");
      Serial.println(keypadNumConvert(setupKey));
    } else {
      Serial.println("Time error");
    }
    segInputLocation(setupKey, 1);
  }

  return totalSecondsSetup = (timerInputSetup[0]*3600*10) + (timerInputSetup[1]*3600) + (timerInputSetup[2]*60*10) + (timerInputSetup[3]*60) + 
  (timerInputSetup[4]*10) + (timerInputSetup[5]);
}