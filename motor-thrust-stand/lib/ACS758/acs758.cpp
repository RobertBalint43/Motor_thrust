#include <Arduino.h>
#include "port_Serial.h"

float R1 = 47 * 10 ^ 3; //trebuie vazut cand facem pcb
float R2 = 33 * 10 ^ 3;
float VCC = 5.00;
float sensitivity = 0.04; // V/A
float offset = 2.5;
int count = 0;
float mean = 0;

void initACS()
{
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

void calcACS(String& serialString)
{
    ADCSRA |= (1 << ADSC);
    uint16_t val = ADCL | (uint16_t)(ADCH << 8);
    //int val = analogRead(A0);
    float voltage = val * (5.0 / 1023.0);
    String voltageOut = String(voltage, 2);
    float current = (voltage - offset) / sensitivity;
    mean = mean + current;
    count++;
    if (count == 1)
    {
        count = 0;
        mean = mean / 5;
        String currentOut = String(mean, 3);
        serialString = serialString + currentOut;
        // sendString(" \nCurentul: ");
        // delay(20);
        // sendString(currentOut);
        mean = 0;
    }
}

void Voltage(String& serialString)
{
    ADMUX |= (1 << MUX0); // channel for A1 
    ADCSRA |= (1 << ADSC);

    uint16_t val = ADCL | (uint16_t)(ADCH << 8);
    float voltage = val * (5.0 / 1023.0) * ((R1 + R2) / R2);
    mean = mean + voltage;
    count++;
    if (count == 1)
    {
        count = 0;
        mean = mean / 5;
        String voltageOut = String(mean, 2);
        serialString = serialString + voltageOut;
        // sendString(" \nBattery voltage: ");
        // delay(20);
        // sendString(voltageOut); 
        mean = 0;
    }
}