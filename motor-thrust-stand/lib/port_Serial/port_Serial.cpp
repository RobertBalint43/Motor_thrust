#include <Arduino.h>
#include "port_Serial.h"

char buffer[32];
volatile int i = 0, j = 0, len = 0;
volatile bool intrerupere, bclear = false;
String saux;


void initHardwareSerial(unsigned long int baud, bool intrerup)
{
  intrerupere = intrerup;
  DDRD |= (1 << PD1);
  PORTD |= (1 << PD1);
  DDRB |= (1 << DDB5);
  uint16_t UBRR = (F_CPU / 16UL / baud) - 1;
  UBRR0H = UBRR >> 8;
  UBRR0L = UBRR; // calculam UBRR
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  if (intrerupere == 1)
  {
    cli();
    UCSR0B |= (1 << RXCIE0);
    sei();
  }
}

void sendChar(char ch)
{
  if (intrerupere == 0)
  {
    while (!(UCSR0A & (1 << UDRE0)))
      ;
    UDR0 = ch;
  }
  else
  {
    char c[2];
    c[0] = ch;
    c[1] = '\0';
    sendUSART(c);
  }
}

void sendString(String s)
{
  if (intrerupere == 0)
  {
    for (unsigned int i = 0; i < s.length(); i++)
    {
      while (!(UCSR0A & (1 << UDRE0)))
        ;
      UDR0 = s[i];
    }
  }
  else
    sendUSART(s);
}

unsigned long int receive()
{
  while (!(UCSR0A & (1 << RXC0)))
    ;
  return UDR0;
}

void sendUSART(String s)
{
  saux = s;
  i = s.length();
  j = 0;
  if (i > 0)
  {
    UDR0 = s[j++]; // adaugam un element in UDR pentru a putea folosi intreruperea
    i--;
    UCSR0B |= (1 << TXCIE0); // Fortam intreruperea
  }
}

void clearBuffer()
{
  strcpy(buffer, "");
  len = 0;
}


ISR(USART_RX_vect)
{
  buffer[len] = UDR0;
  len++;
  if (len == 32)
  {
    len = 0;
  }
}

ISR(USART_TX_vect)
{
  if (i > 0)
  {
    UDR0 = saux[j++];
    i--;
  }
  else
  {
    UCSR0B &= ~(1 << TXCIE0);
  }
}
