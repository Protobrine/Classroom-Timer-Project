#include <Arduino.h>
#include "functions.h"
byte num = 0;

byte keypadNumConvert(char keyInput) {
  switch (keyInput)
  {
  case '0':
    num = 0;
    return num;
    break;
  case '1':
    num = 1;
    return num;
    break;
  case '2':
    num = 2;
    return num;
    break;
  case '3':
    num = 3;
    return num;
    break;
  case '4':
    num = 4;
    return num;
    break;
  case '5':
    num = 5;
    return num;
    break;
  case '6':
    num = 6;
    return num;
    break;
  case '7':
    num = 7;
    return num;
    break;
  case '8':
    num = 8;
    return num;
    break;
  case '9':
    num = 9;
    return num;
    break;
  }
  return 10;
}