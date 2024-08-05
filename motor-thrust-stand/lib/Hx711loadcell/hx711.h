#ifndef LOADCELL
#define LOADCELL

#include <stdlib.h>

extern long int Count;

long int readWeight();
void initLoadCell();
float calibration(long int);
void sendWeight(String&);
void TARE();


#endif
