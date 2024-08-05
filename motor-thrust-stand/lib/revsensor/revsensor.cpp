#include <Arduino.h>
#include "port_Serial.h"
#include "acs758.h"
#include "esccontroller.h"
volatile float rotatii, RPM, lastinterval = 0, interval, period = 0;
void initSensor()
{
    DDRD &= ~(1 << PD2); // input
    PIND |= (1 << PD2);
    EICRA |= (1 << ISC01);
    EIMSK |= (1 << INT0);
    sei();
}

void calcRPM(String& serialString)
{
 if (period > 0) {
        RPM = 60000000.0 / period;
    } else {
        RPM = 0;
    }
    String RPM_s = String(RPM, 2);
    serialString = serialString + RPM_s;
    // sendString("\nRPM:");
    // delay(20);
    // sendString(serialString);
    // delay(20);
}

ISR(INT0_vect)
{
    interval = micros();
    period = interval - lastinterval;
    lastinterval = interval;
}
