#ifndef Delay_H_
#define Delay_H_

#include "Arduino.h"

#define DELAY_FREQ_STEP_MAX 100

// "waste" one cycle (62.5ns) on a 16MHz Arduino
#define NOP __asm__ __volatile__ ("nop\n\t")

// delay in nanoseconds for single loop - one #NOP call in for-loop.
#define DELAY_NOP_NS 440UL

// enabling delay function triggers extra method call, NOP loop is inside this call.
#define DELAY_ENABLED_NS 1140UL

extern boolean delayOn;

void delay_wait();
uint16_t delay_nextStep();
uint32_t delay_up();
uint32_t delay_down();
void delay_setup(uint32_t _maxDelayNs, uint16_t _initDelayNop);

inline uint32_t delay_calcDelayNs(uint16_t delayNop) {
	return (uint32_t) delayNop * DELAY_NOP_NS + (delayNop == 0 ? 0 : DELAY_ENABLED_NS);
}

#endif /* Delay_H_ */
