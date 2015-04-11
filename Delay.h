#ifndef Delay_H_
#define Delay_H_
#include "Arduino.h"
#include "LCD.h"

#define FREQ_STEP_MAX 10000

void delay_loop();
void delay_freqStep();
void delay_freqUp();
void delay_freqDown();

#endif /* Delay_H_ */
