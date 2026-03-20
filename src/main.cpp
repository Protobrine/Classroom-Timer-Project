#include <Arduino.h>
#include <Keypad.h>
#include "functions.h"
#include <WiFi.h>
#include "time.h"

// Replace with your network credentials
const char* ssid = "PLDTHOMEFIBR48EUV"; // WIFI name: PLDTHOMEFIBR48EUV
const char* password = "PLDTWIFIXyFyz"; // WIFI Password: PLDTWIFIXyFyz

// NTP server setup
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 28800;    // Adjust this for your timezone
const int daylightOffset_sec = 0;  // Adjust if DST is in effect
unsigned int NTPDelay;
byte tryNetwork = 0; // 0 - Wifi not connected | 1 - Wifi connected

const int oneSec = 1000;
unsigned long prevSecTime = 0;
unsigned long totalSeconds = 0; // Change the number to set how many seconds it will countdown

byte stopStart = 0; // 0 = Pause |  1 = Start
byte setupMode = 0; // 0 = noSetup | 1 = setupMode
byte changeDisplay = 0; // 0 = Clock | 1 = Timer
unsigned long prevDisplaySec = 0;

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

void printDateTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  char formattedTime[80];  // Buffer to store the formatted string
  strftime(formattedTime, sizeof(formattedTime), "%A, %B %d %Y %H:%M:%S", &timeinfo);
  Serial.println(formattedTime);
}

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

  if (tryNetwork == 0) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(500);
    }
    Serial.println("\nConnected to WiFi!");

    // Configure NTP
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    Serial.println("NTP time configured.");
    tryNetwork = 1;
  }

}

void loop() {
  unsigned long currentTime = millis();
  char key = keypad.getKey();
  byte inputLoc;

  if (setupMode == 0 && changeDisplay == 1)
  {
    timerDisplay(totalSeconds, inputLoc, setupMode, prevDisplaySec);
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
    Serial.print("Main check: ");
    Serial.println(currentTime);
    printDateTime();
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

  //Setup Mode
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

  if (setupMode == 1 && changeDisplay == 1) {
    inputLoc = segInputLocation(key);
    totalSeconds = timerSetup(key, inputLoc);
    timerDisplay(totalSeconds, inputLoc, setupMode, prevDisplaySec);
  }  
  // Change display
  if (key == 'D' && changeDisplay == 0) {
    changeDisplay = 1;
    prevDisplaySec = currentTime;
    Serial.println("Display changed to timer");
  } else if (key == 'D' && changeDisplay == 1) {
    changeDisplay = 0;
    Serial.println("Display changed to clock");
  } 
  
}