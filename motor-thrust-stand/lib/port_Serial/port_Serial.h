#ifndef PORTSERIAL
#define PORTSERIAL

#include <stdint.h>

#define BIT_TIME 13
/*#define BAUD_600 600
#define BAUD_1200 1200
#define BAUD_2400 2400
#define BAUD_4800 4800
#define BAUD_9600 9600
#define BAUD_19200 19200
#define BAUD_38400 38400

#define BAUD_RATE   BAUD_4800
//#define UBRR (F_CPU / 16UL / BAUD_RATE) - 1 //calculam UBRR*/

extern char buffer[32];
extern volatile int len;

void initHardwareSerial(unsigned long int, bool);
void sendChar(char);
void sendString(String);
unsigned long int receive();
void sendUSART(String);
void clearBuffer();
#endif