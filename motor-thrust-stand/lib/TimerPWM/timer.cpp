#include <Arduino.h>
#include "port_Serial.h"

void initTimer()
{
  DDRD |= (1 << PD6); // activam output pwm
  TCCR0A = 0;
  TCCR0B = 0;
  TCCR0A |= (1 << COM0A1) | (1 << WGM02) | (1 << WGM01) | (1 << WGM00); // fast pwm
  TCCR0A |= (1 << COM0B1);
  TCCR0A &= ~(1 << COM0A0);
  TCCR0A &= ~(1 << COM0B0); // clear OCROA when down counting
  TCCR0B |= (1 << CS01);
  TCCR0B &= ~(1 << CS02);
  TCCR0B &= ~(1 << CS00); // prescaler 8
}

void setPWM()
{

  if (len == 3)
  {
    buffer[3] = '\0';
    int dutyCycle = atoi(buffer);
    OCR0A = (dutyCycle * 255) / 100;
    len = 0;
  }
}
