#include <Arduino.h>
#include "acs758.h"
#include "esccontroller.h"
#include "hx711.h"
#include "port_Serial.h"
#include "timer.h"
#include "revsensor.h"

float CountAux;
int command = 0;
char bufferaux[64];
int ok = 0;
String serialString;

void readCommand()
{
  command = 0;
  if (strstr(buffer, "MS:") != NULL)
  {
    command = 1;
  }
  if (strstr(buffer, "W:") != NULL)
  {
    command = 2;
  }
  if (strstr(buffer, "C:") != NULL)
  {
    command = 3;
  }
  if (strstr(buffer, "TARE") != NULL)
  {
    command = 4;
  }
}

void setup()
{
  initHardwareSerial(1000000, 1);
  initACS();
  initLoadCell();
  initESC();
  initSensor();
}
void loop()
{
  readCommand();
  switch (command)
  {
  case 1:
    setPWMESC();
    break;
  case 2:
    sendString("\nSetam greutatea impinsa!");
    delay(30);
    clearBuffer();
    break;
  case 3:
    sendString("\nSetam curentul cerut!\n");
    delay(30);
    clearBuffer();
    break;
  case 4:
    sendString("TARE");
    delay(30);
    TARE();
    clearBuffer();
  default:
    sendString("\nNu setam nimic!\n");
    delay(30);
    clearBuffer();
    break;
  }
  
  sendWeight(serialString);
  serialString = serialString + ":";
  calcRPM(serialString);
  serialString = serialString + ":";
  calcACS(serialString);
  serialString = serialString + ":";
  Voltage(serialString);
  serialString = serialString + ":";
  getPWM(serialString);

  sendString(serialString);
  delay(30);
  serialString = "\0";
  delay(200);
}
