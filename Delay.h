#ifndef Delay_H_
#define Delay_H_

#include "Arduino.h"

#define DELAY_FREQ_STEP_MAX 1000

// "waste" one cycle (62.5ns) on a 16MHz Arduino
#define NOP __asm__ __volatile__ ("nop\n\t")

// delay in nanoseconds for single loop - one #NOP call in for-loop.
#define DELAY_NOP_NS 440UL

// enabling delay function triggers extra method call, NOP loop is inside this call.
#define DELAY_ENABLED_NS 1140UL

/*
1300
2880
3320
3740
4200

460
420
440
 */

extern boolean delay_on;

void delay_wait();
uint16_t delay_nextStep();
uint32_t delay_up();
uint32_t delay_down();
uint32_t delay_stepDelayNs();
void delay_setMaxDelayNs(uint32_t _maxDelayNs);
uint16_t delay_reset();

#endif /* Delay_H_ */
