#ifndef Delay_H_
#define Delay_H_
#include "Arduino.h"
#include "LCD.h"

#define DELAY_FREQ_STEP_MAX 1000
#define DELAY_FREQ_STEP_CHARS 4

// "waste" one cycle (62.5ns) on a 16MHz Arduino
#define NOP __asm__ __volatile__ ("nop\n\t")

// delay in nanoseconds for single loop - one #NOP call in for-loop.
#define DELAY_NOP_NS 440UL

void delay_setup();
void delay_wait();
void delay_step();
void delay_up();
void delay_down();
uint32_t delay_waitNs();

#endif /* Delay_H_ */
