#include <Arduino.h>
#include "esccontroller.h"
#include "port_Serial.h"

volatile long int low, high;
int dutyCycleMap = 0, dutyCycle = 0;
void initESC()
{
    DDRB |= (1 << PB1); // activam output pwm pe OC1A
    TCCR1A = 0;         // Clear TCCR1A register
    TCCR1B = 0;         // Clear TCCR1B register
    TCNT1 = 0;          // Clear counter
    TCCR1B |= (1 << WGM13);
    TCCR1B |= (1 << CS11);   // prescaler 8
    TCCR1A |= (1 << COM1A1); // non inverting
    ICR1 = 9999;             // T = 16MHz/64 = 250000Hz = 4 micros; frecv ESC = 75Hz =? Tf = 13333 microsec; ICR = Tf/4 = 3332, deci dupa 3332 cicluri face o citire ESC-ul
    low = 1000;              // Motorul ia valori intre 1 ms si 2ms => 1000mcs - 2000mcs / 4 => 250 ciclii - 500 ciclii
    high = 2000;
}

void setPWMESC()
{
    dutyCycle = (buffer[3] - 48) * 100 + (buffer[4] - 48) * 10 + (buffer[5] - 48);
    dutyCycleMap = map(dutyCycle, 0, 100, low, high);
    OCR1A = dutyCycleMap;
    clearBuffer();
}

void getPWM(String& serialString){
    String dutyCycleS = String(dutyCycle);
    serialString = serialString + dutyCycleS +"%";       
}