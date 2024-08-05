#ifndef ESCController
#define ESCController

#include <stdint.h>

extern char buffer[32];
extern volatile int len;

void initESC();
void setPWMESC();
void getPWM(String&);

#endif