#ifndef timer
#define timer


extern char buffer[32];
extern volatile int len;

void initTimer();
void setPWM();

#endif