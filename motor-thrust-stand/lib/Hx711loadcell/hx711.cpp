#include <Arduino.h>
#include "port_Serial.h"

#define DOUT_LOW PORTD &= ~(1 << PD3);
#define DOUT_HIGH PORTD |= (1 << PD3);
#define SCK_LOW PORTD &= ~(1 << PD4);
#define SCK_HIGH PORTD |= (1 << PD4);

volatile long int Count, tareOffset = 8428808;

void initLoadCell() {
  DDRD |= (1 << PD4);  // SCK output
  DDRD &= ~(1 << PD3); // DOUT input
}

long int readWeight() {
  char i;
  DOUT_HIGH;
  SCK_LOW;
  Count = 0;
  while (PIND & (1 << PD3));
  for (i = 0; i < 24; i++) {
    SCK_HIGH;
    Count = Count << 1;
    SCK_LOW;
    if (PIND & (1 << PD3))
      Count++;
  }
  DOUT_HIGH;
  Count ^= 0x800000;
  DOUT_LOW;
  return Count;
}

float calibration(long int Count) {
  float scale = 5000.0 / 1890317.0;
  float CountAux = (Count - tareOffset) * scale;
  return CountAux;
}//10309125

void sendWeight(String& serialString){
  long int Count2 = readWeight();
  float CountAux2 = calibration(Count2);
  String CountString = String(CountAux2,2);
  serialString = serialString + CountString;
  // sendString("\nGreutatea(grame):");
  // delay(30);
  // sendString(serialString);
  // delay(20);
}

void TARE(){
     tareOffset = readWeight();
}
