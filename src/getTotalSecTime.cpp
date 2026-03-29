#include <Arduino.h>
#include "functions.h"

unsigned long timeTotalSec = 0;

unsigned long getTotalSecTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time function");
    return 0;
  }

  //%H = hours | %M = Minutes | %S = Seconds
  char timeHours[80];
  char timeMinutes[80];
  char timeSeconds[80];


  strftime(timeHours, sizeof(timeHours), "%H", &timeinfo);
  strftime(timeMinutes, sizeof(timeMinutes), "%M", &timeinfo);
  strftime(timeSeconds, sizeof(timeSeconds), "%S", &timeinfo);

  unsigned int clockHrs = atoi(timeHours);
  unsigned int clockMin = atoi(timeMinutes);
  unsigned int clockSec = atoi(timeSeconds);
  
  timeTotalSec = + (clockHrs*3600) + (clockMin*60) + (clockSec);
  return timeTotalSec;
}