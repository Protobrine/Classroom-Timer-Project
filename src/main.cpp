#include <Arduino.h>
#include <Keypad.h>
#include <WiFi.h>
#include "esp_sntp.h"
#include "functions.h"
#include "time.h"

// Replace with your network credentials
const char* ssid = "PLDTHOMEFIBR48EUV"; // WIFI name: PLDTHOMEFIBR48EUV
const char* password = "PLDTWIFIXyFyz"; // WIFI Password: PLDTWIFIXyFyz

// NTP server setup
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 28800;    // Adjust this for your timezone
const int daylightOffset_sec = 0;  // Adjust if DST is in effect
unsigned int NTPDelay;
unsigned int connectingLength = 5000;
byte tryNetwork = 0; // 0 - Wifi not connected | 1 - Wifi connectedb
byte instabilityChange = 0; // 0 - no instability | 1 - instability
byte changePrevNTP = 0; 

// Countdown timer and checker
const int oneSec = 1000;
unsigned long prevSecTime = 0;
unsigned long totalSeconds = 0; // Change the number to set how many seconds it will countdown

byte stopStart = 0; // 0 = Pause |  1 = Start
byte setupMode = 0; // 0 = noSetup | 1 = setupMode
byte changeDisplay = 0; // 0 = Clock | 1 = Timer
unsigned long prevDisplaySec = 0;

// Every minute change display
unsigned int oneMinute = 60000; // one minute
unsigned long prevChangeDisp = 0;

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

  pinMode(buzzer, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();
  char key = keypad.getKey();
  byte inputLoc;
  if (setupMode == 0 && stopStart == 1) {
    ringBuzzer(totalSeconds);
  }

  // NTP Things
  if (tryNetwork == 0) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    Serial.println("\nConnected to WiFi!");

    // Configure NTP
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    Serial.println("NTP time configured.");
    tryNetwork = 1;
  }

  if (instabilityChange == 0) {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo, connectingLength)) {
      Serial.println("Failed to obtain time main");
      sntp_stop();
      instabilityChange = 1;
      Serial.print("Instability check: ");
      Serial.println(instabilityChange);

      prevDisplaySec = currentTime + connectingLength + 1000;
      
    } else if (changePrevNTP == 0) {

      prevDisplaySec = currentTime + connectingLength;
      Serial.print("Prev time: ");
      Serial.println(prevDisplaySec);
      changePrevNTP = 1;
    }
  }
  
  if (setupMode == 0 && changeDisplay == 1) {
    timerDisplay(totalSeconds, inputLoc, setupMode, prevDisplaySec);
  }

  if (setupMode == 0 && changeDisplay == 0 && instabilityChange == 0) {
    unsigned long totalClockTime = getTotalSecTime();
    clockDisplay(totalClockTime, prevDisplaySec, instabilityChange);
  }

  if (setupMode == 0 && changeDisplay == 0 && instabilityChange == 1) {
    byte totalClockTime = 0;
    clockDisplay(totalClockTime, prevDisplaySec, instabilityChange);
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
/*     Serial.print("Seconds check: ");
    Serial.println(totalSeconds);
    Serial.print("Main check: ");
    Serial.println(currentTime);

    if (instabilityChange == 0) {
      unsigned long totalClockTime = getTotalSecTime();
      struct tm timeinfo;

      Serial.print("Clock sec check: ");
      Serial.println(totalClockTime);
      Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    } */
    prevSecTime += oneSec;
  }

  if (key) {
    Serial.println(key);
  }

  // Stop and Start
  if (key == 'A' && stopStart == 0 && setupMode == 0) {
    stopStart = 1;
    changeDisplay = 1;
    prevSecTime = currentTime;
    prevChangeDisp = currentTime;
    Serial.println("Timer Start");
  } else if (key == 'A' && stopStart == 1 && setupMode == 0) {
    stopStart = 0;
    changeDisplay = 1;
    Serial.println("Timer pause");
  }

  //Setup Mode
  if (key == 'C' && setupMode == 0 && changeDisplay == 1) {
    setupMode = 1;
    stopStart = 0;
    Serial.println("Setup  on");
  } else if (key == 'C' && setupMode == 1 && changeDisplay == 1) {
    setupMode = 0;
    stopStart = 0;
    prevSecTime = currentTime;
    Serial.println("Setup  off");
  }

  if (setupMode == 1 && changeDisplay == 1) {
    inputLoc = segInputLocation(key);
    totalSeconds = timerSetup(key, inputLoc);
    timerDisplay(totalSeconds, inputLoc, setupMode, prevDisplaySec);
  }  
  // Change display
  if (key == 'D' && changeDisplay == 0 && setupMode == 0) {
    changeDisplay = 1;
    prevDisplaySec = currentTime;
    prevChangeDisp = currentTime;
    Serial.println("Display changed to timer");
  } else if (key == 'D' && changeDisplay == 1 && setupMode == 0) {
    changeDisplay = 0;
    prevDisplaySec = currentTime;
    prevChangeDisp = currentTime;
    Serial.println("Display changed to clock");
  }

  // Change display every minute
  if (stopStart == 1 && instabilityChange == 0) {
    if (currentTime - prevChangeDisp >= oneMinute) {
      if (changeDisplay == 1) {
        changeDisplay = 0;
      } else if (changeDisplay == 0) {
        changeDisplay = 1;
      }
      prevChangeDisp += oneMinute;
    }
  }
}