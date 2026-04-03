#include <Arduino.h>
#include "functions.h"

byte buzzerSwitch = 0;

unsigned int blank = 1000; // Space in the morse code or after a sequence
unsigned int buzzInterval = 500; // Interval between beeps
unsigned int chosenDelay = 0; // if short or long is last beep

unsigned int buzzDot = 200; // short dot beep
unsigned int buzzLong = 1000; // long dot beep

unsigned long prevMilliBuzz = 0;
unsigned long prevMilliBuzz1 = 0;

byte buzzSetup = 0; // sets up the buzz for the next sequence
byte buzzRepeat = 0; // How many times the dot or long will beep
byte buzzRepeat2 = 0; // How many times the pattern will repeat on variable buzzRepeat
byte buzzAlternate = 0; // If the pattern is alternating between dot or long
byte changeBuzz = 0; // The pattern will change
byte absoluteZero = 0; // 0 - not yet alarmed | 1 - alarmed

void ringBuzzer(unsigned long buzzTotalSeconds) {
  unsigned long currentTime = millis();

  if (buzzTotalSeconds == 3600 && buzzSetup == 0) {
    prevMilliBuzz = currentTime;
    prevMilliBuzz1 = currentTime;
    buzzSetup = 1;

    buzzRepeat2 = 0;
    absoluteZero = 0;
  } else if (buzzTotalSeconds == 2700 && buzzSetup == 0) {
    prevMilliBuzz = currentTime;
    prevMilliBuzz1 = currentTime;
    buzzSetup = 1;

    buzzRepeat2 = 0;
    absoluteZero = 0;
  } else if (buzzTotalSeconds == 1800 && buzzSetup == 0) {
    prevMilliBuzz = currentTime;
    prevMilliBuzz1 = currentTime;
    buzzSetup = 1;

    buzzRepeat2 = 0;
    absoluteZero = 0;
  } else if (buzzTotalSeconds == 900 && buzzSetup == 0) {
    prevMilliBuzz = currentTime;
    prevMilliBuzz1 = currentTime;
    buzzSetup = 1;

    buzzRepeat2 = 0;
    absoluteZero = 0;
  } else if (buzzTotalSeconds == 600 && buzzSetup == 0) {
    prevMilliBuzz = currentTime;
    prevMilliBuzz1 = currentTime;
    buzzSetup = 1;

    buzzRepeat2 = 0;
    absoluteZero = 0;
  } else if (buzzTotalSeconds == 300 && buzzSetup == 0) {
    prevMilliBuzz = currentTime;
    prevMilliBuzz1 = currentTime;
    buzzSetup = 1;

    buzzRepeat2 = 0;
    absoluteZero = 0;
  } else if (buzzTotalSeconds == 60 && buzzSetup == 0) {
    prevMilliBuzz = currentTime;
    prevMilliBuzz1 = currentTime;
    buzzSetup = 1;

    buzzRepeat2 = 0;
    absoluteZero = 0;
  } else if (buzzTotalSeconds == 0 && buzzSetup == 0) {
    prevMilliBuzz = currentTime;
    prevMilliBuzz1 = currentTime;
    buzzSetup = 1;

    buzzRepeat2 = 0;
  }

  //60 minutes
  if (buzzTotalSeconds <= 3600 && buzzTotalSeconds > 2700) {
    if (buzzRepeat2 <= 1) {
      if (buzzRepeat <= 3) {
        if (currentTime - prevMilliBuzz <= buzzDot) {
          digitalWrite(buzzer, HIGH);
        }
        if (currentTime - prevMilliBuzz > buzzDot && currentTime - prevMilliBuzz <= buzzDot + buzzInterval) {
          digitalWrite(buzzer, LOW);
        }
        if (currentTime - prevMilliBuzz >= buzzDot + buzzInterval) {
          prevMilliBuzz += buzzDot + buzzInterval;
          buzzRepeat++;
          Serial.print("Buzz test: ");
          Serial.println(prevMilliBuzz);
        }
      }
      if (currentTime - prevMilliBuzz1 >= (buzzDot + buzzInterval)*4 + blank) {
        prevMilliBuzz1 += (buzzDot + buzzInterval)*4 + blank;
        prevMilliBuzz += blank; 
        buzzRepeat2++;
        buzzRepeat = 0;
        Serial.print("Buzz test 2: ");
        Serial.println(prevMilliBuzz1);
      }
      if (buzzRepeat2 == 1) {
        buzzSetup = 0;
      }
    }
  }

  // 45 minutes
  if (buzzTotalSeconds <= 2700 && buzzTotalSeconds > 1800) {
    if (buzzRepeat2 <= 1) {
      if (buzzRepeat <= 2) {
        if (currentTime - prevMilliBuzz <= buzzDot) {
          digitalWrite(buzzer, HIGH);
        }
        if (currentTime - prevMilliBuzz > buzzDot && currentTime - prevMilliBuzz <= buzzDot + buzzInterval) {
          digitalWrite(buzzer, LOW);
        }
        if (currentTime - prevMilliBuzz >= buzzDot + buzzInterval) {
          prevMilliBuzz += buzzDot + buzzInterval;
          buzzRepeat++;
          Serial.print("Buzz test: ");
          Serial.println(prevMilliBuzz);
        }
      }
      if (currentTime - prevMilliBuzz1 >= (buzzDot + buzzInterval)*3 + blank) {
        prevMilliBuzz1 += (buzzDot + buzzInterval)*3 + blank;
        prevMilliBuzz += blank; 
        buzzRepeat2++;
        buzzRepeat = 0;
        Serial.print("Buzz test 2: ");
        Serial.println(prevMilliBuzz1);
      }
      if (buzzRepeat2 == 1) {
        buzzSetup = 0;
      }
    }
  }

  // 30 minutes
  if (buzzTotalSeconds <= 1800 && buzzTotalSeconds > 900) {
    if (buzzRepeat2 <= 1) {
      if (buzzRepeat <= 1) {
        if (currentTime - prevMilliBuzz <= buzzDot) {
          digitalWrite(buzzer, HIGH);
        }
        if (currentTime - prevMilliBuzz > buzzDot && currentTime - prevMilliBuzz <= buzzDot + buzzInterval) {
          digitalWrite(buzzer, LOW);
        }
        if (currentTime - prevMilliBuzz >= buzzDot + buzzInterval) {
          prevMilliBuzz += buzzDot + buzzInterval;
          buzzRepeat++;
          Serial.print("Buzz test: ");
          Serial.println(prevMilliBuzz);
        }
      }
      if (currentTime - prevMilliBuzz1 >= (buzzDot + buzzInterval)*2 + blank) {
        prevMilliBuzz1 += (buzzDot + buzzInterval)*2 + blank;
        prevMilliBuzz += blank; 
        buzzRepeat2++;
        buzzRepeat = 0;
        Serial.print("Buzz test 2: ");
        Serial.println(prevMilliBuzz1);
      }
      if (buzzRepeat2 == 1) {
        buzzSetup = 0;
      }
    }
  }

  // 15 minutes
  if (buzzTotalSeconds <= 900 && buzzTotalSeconds > 600) {
    if (buzzRepeat2 <= 1) {
      if (buzzRepeat <= 3) {
        if (buzzRepeat == 0) {
          if (currentTime - prevMilliBuzz <= buzzLong) {
            digitalWrite(buzzer, HIGH);
            chosenDelay = buzzLong;
          }
          if (currentTime - prevMilliBuzz > chosenDelay && currentTime - prevMilliBuzz <= chosenDelay + buzzInterval) {
            digitalWrite(buzzer, LOW);
          }
        } else if (buzzRepeat > 0) {
          if (currentTime - prevMilliBuzz <= buzzDot) {
            digitalWrite(buzzer, HIGH);
            chosenDelay = buzzDot;
          }
          if (currentTime - prevMilliBuzz > chosenDelay && currentTime - prevMilliBuzz <= chosenDelay + buzzInterval) {
            digitalWrite(buzzer, LOW);
          }
        }
        if (currentTime - prevMilliBuzz >= chosenDelay + buzzInterval) {
          prevMilliBuzz += chosenDelay + buzzInterval;
          buzzRepeat++;
          Serial.print("Buzz test: ");
          Serial.println(prevMilliBuzz);
        }
      }
      if (currentTime - prevMilliBuzz1 >= (buzzLong + buzzInterval) + (buzzDot + buzzInterval)*3 + blank) {
        prevMilliBuzz1 += (buzzLong + buzzInterval) + (buzzDot + buzzInterval)*3 + blank;
        prevMilliBuzz += blank; 
        buzzRepeat2++;
        buzzRepeat = 0;
        Serial.print("Buzz test 2: ");
        Serial.println(prevMilliBuzz1);
      }
      if (buzzRepeat2 == 1) {
        buzzSetup = 0;
      }
    }
  }

  // 10 minutes
  if (buzzTotalSeconds <= 600 && buzzTotalSeconds > 300) {
    if (buzzRepeat2 <= 1) {
      if (buzzRepeat <= 2) {
        if (buzzRepeat == 0) {
          if (currentTime - prevMilliBuzz <= buzzLong) {
            digitalWrite(buzzer, HIGH);
            chosenDelay = buzzLong;
          }
          if (currentTime - prevMilliBuzz > chosenDelay && currentTime - prevMilliBuzz <= chosenDelay + buzzInterval) {
            digitalWrite(buzzer, LOW);
          }
        } else if (buzzRepeat > 0) {
          if (currentTime - prevMilliBuzz <= buzzDot) {
            digitalWrite(buzzer, HIGH);
            chosenDelay = buzzDot;
          }
          if (currentTime - prevMilliBuzz > chosenDelay && currentTime - prevMilliBuzz <= chosenDelay + buzzInterval) {
            digitalWrite(buzzer, LOW);
          }
        }
        if (currentTime - prevMilliBuzz >= chosenDelay + buzzInterval) {
          prevMilliBuzz += chosenDelay + buzzInterval;
          buzzRepeat++;
          Serial.print("Buzz test: ");
          Serial.println(prevMilliBuzz);
        }
      }
      if (currentTime - prevMilliBuzz1 >= (buzzLong + buzzInterval) + (buzzDot + buzzInterval)*2 + blank) {
        prevMilliBuzz1 += (buzzLong + buzzInterval) + (buzzDot + buzzInterval)*2 + blank;
        prevMilliBuzz += blank; 
        buzzRepeat2++;
        buzzRepeat = 0;
        Serial.print("Buzz test 2: ");
        Serial.println(prevMilliBuzz1);
      }
      if (buzzRepeat2 == 1) {
        buzzSetup = 0;
      }
    }
  }

  // 5 minutes
  if (buzzTotalSeconds <= 300 && buzzTotalSeconds > 60) {
    if (buzzRepeat2 <= 1) {
      if (buzzRepeat <= 1) {
        if (buzzRepeat == 0) {
          if (currentTime - prevMilliBuzz <= buzzLong) {
            digitalWrite(buzzer, HIGH);
            chosenDelay = buzzLong;
          }
          if (currentTime - prevMilliBuzz > chosenDelay && currentTime - prevMilliBuzz <= chosenDelay + buzzInterval) {
            digitalWrite(buzzer, LOW);
          }
        } else if (buzzRepeat > 0) {
          if (currentTime - prevMilliBuzz <= buzzDot) {
            digitalWrite(buzzer, HIGH);
            chosenDelay = buzzDot;
          }
          if (currentTime - prevMilliBuzz > chosenDelay && currentTime - prevMilliBuzz <= chosenDelay + buzzInterval) {
            digitalWrite(buzzer, LOW);
          }
        }
        if (currentTime - prevMilliBuzz >= chosenDelay + buzzInterval) {
          prevMilliBuzz += chosenDelay + buzzInterval;
          buzzRepeat++;
          Serial.print("Buzz test: ");
          Serial.println(prevMilliBuzz);
        }
      }
      if (currentTime - prevMilliBuzz1 >= (buzzLong + buzzInterval) + (buzzDot + buzzInterval)*1 + blank) {
        prevMilliBuzz1 += (buzzLong + buzzInterval) + (buzzDot + buzzInterval)*1 + blank;
        prevMilliBuzz += blank; 
        buzzRepeat2++;
        buzzRepeat = 0;
        Serial.print("Buzz test 2: ");
        Serial.println(prevMilliBuzz1);
      }
      if (buzzRepeat2 == 1) {
        buzzSetup = 0;
      }
    }
  }

  // 1 minute
  if (buzzTotalSeconds <= 60 && buzzTotalSeconds > 0) {
    if (buzzRepeat2 <= 3) {
      if (buzzRepeat <= 3) {
        if (buzzAlternate == 1) {
          if (currentTime - prevMilliBuzz <= buzzLong) {
            digitalWrite(buzzer, HIGH);
            chosenDelay = buzzLong;
          }
          if (currentTime - prevMilliBuzz > chosenDelay && currentTime - prevMilliBuzz <= chosenDelay + buzzInterval) {
            digitalWrite(buzzer, LOW);
          }
        } else if (buzzAlternate == 0) {
          if (currentTime - prevMilliBuzz <= buzzDot) {
            digitalWrite(buzzer, HIGH);
            chosenDelay = buzzDot;
          }
          if (currentTime - prevMilliBuzz > chosenDelay && currentTime - prevMilliBuzz <= chosenDelay + buzzInterval) {
            digitalWrite(buzzer, LOW);
          }
        }
        if (currentTime - prevMilliBuzz >= chosenDelay + buzzInterval) {
          prevMilliBuzz += chosenDelay + buzzInterval;
          buzzRepeat++;

          if (buzzAlternate == 0) {
            buzzAlternate = 1;
          } else if (buzzAlternate = 1) {
            buzzAlternate = 0;
          }          

          Serial.print("Buzz test: ");
          Serial.println(prevMilliBuzz);
        }
      }
      if (currentTime - prevMilliBuzz1 >= (buzzLong + buzzInterval)*2 + (buzzDot + buzzInterval)*2 + blank) {
        prevMilliBuzz1 += (buzzLong + buzzInterval)*2 + (buzzDot + buzzInterval)*2 + blank;
        prevMilliBuzz += blank; 
        buzzRepeat2++;
        buzzRepeat = 0;
        Serial.print("Buzz test 2: ");
        Serial.println(prevMilliBuzz1);
      }
      if (buzzRepeat2 == 3) {
        buzzSetup = 0;
      }
    }
  }

  // time = 0
  if (buzzTotalSeconds == 0 && absoluteZero == 0) {
    if (buzzRepeat2 <= 21) {
      if (buzzRepeat2 >= 1) {
        changeBuzz = 1;
      }
      if (buzzRepeat <= 3 && changeBuzz == 0) {
        if (currentTime - prevMilliBuzz <= buzzLong) {
          digitalWrite(buzzer, HIGH);
        }
        if (currentTime - prevMilliBuzz > buzzLong && currentTime - prevMilliBuzz <= buzzLong + buzzInterval) {
          digitalWrite(buzzer, LOW);
        }
        if (currentTime - prevMilliBuzz >= buzzLong + buzzInterval) {
          prevMilliBuzz += buzzLong + buzzInterval;
          buzzRepeat++;
          Serial.print("Buzz test: ");
          Serial.println(prevMilliBuzz);
        }
      }
      if (buzzRepeat <= 2 && changeBuzz == 1) {
        if (currentTime - prevMilliBuzz <= buzzDot) {
          digitalWrite(buzzer, HIGH);
        }
        if (currentTime - prevMilliBuzz > buzzDot && currentTime - prevMilliBuzz <= buzzDot + buzzInterval) {
          digitalWrite(buzzer, LOW);
        }
        if (currentTime - prevMilliBuzz >= buzzDot + buzzInterval) {
          prevMilliBuzz += buzzDot + buzzInterval;
          buzzRepeat++;
          Serial.print("Buzz test: ");
          Serial.println(prevMilliBuzz);
        }
      }
      if (currentTime - prevMilliBuzz1 >= (buzzLong + buzzInterval)*4 + blank && changeBuzz == 0) {
        prevMilliBuzz1 += (buzzLong + buzzInterval)*4 + blank;
        prevMilliBuzz += blank; 
        buzzRepeat2++;
        buzzRepeat = 0;
        Serial.print("Buzz test 2: ");
        Serial.println(prevMilliBuzz1);
      }
      if (currentTime - prevMilliBuzz1 >= (buzzDot + buzzInterval)*3 + blank && changeBuzz == 1) {
        prevMilliBuzz1 += (buzzDot + buzzInterval)*3 + blank;
        prevMilliBuzz += blank; 
        buzzRepeat2++;
        buzzRepeat = 0;
        Serial.print("Buzz test 2: ");
        Serial.println(prevMilliBuzz1);
      }
      if (buzzRepeat2 == 22) {
        buzzSetup = 0;
        absoluteZero = 1;
        changeBuzz = 0;
      }
    }
  }
}