#ifndef WAVE_H_
#define WAVE_H_

#include "Arduino.h"

// time for single step of sine wave. Single period consists of #SIN_TABLE_SIZE steps
const static uint32_t WAVE_SIN_STEP_NS = 1507UL;
const static uint32_t WAVE_SQUARE_STEP_NS = 1507UL;
const static uint32_t WAVE_SAW_STEP_NS = 1507UL;
const static uint8_t WAVE_FREQ_STEP_MAX = 100;
const static uint8_t WAVE_FREQ_STEP_INIT = 1;

// "waste" one cycle (62.5ns) on a 16MHz Arduino
#define NOP __asm__ __volatile__ ("nop\n\t")

// delay in nanoseconds for single loop - one #NOP call in for-loop.
const static uint32_t WAVE_NOP_NS = 440UL;

// enabling delay function triggers extra method call, NOP loop is inside this call.
const static uint32_t WAVE_DELAY_ENABLED_NS = 1140UL;

// cycle cannot take longer than 2^32 ns
const static uint32_t WAVE_MAX_CYCLE_TIME_NS = 2147483648UL;

extern boolean wave_delayOn;
extern uint8_t *wave_tablePointer;
extern uint8_t *wave_tableStart;
extern uint16_t wave_tableIdx;
extern uint16_t wave_tableSize;

enum WaveDef {
	SINE = 0,
	SINE_MAX = 1,
	SAW = 2,
	SQUARE_10 = 3,
	SQUARE_20 = 4,
	SQUARE_30 = 5,
	SQUARE_50 = 6,
	SQUARE_70 = 7,
	_FIRST = SINE,
	_LAST = SQUARE_70
};

typedef struct {
	uint32_t fullPeriodNs;
	uint32_t freq;
	WaveDef wave;
	uint16_t delayStep;
} Frequency;

Frequency* wave_setup();
void wave_wait();
uint16_t wave_delayNextStep();
Frequency* wave_delayUp();
Frequency* wave_delayDown();
Frequency* wave_netxWave();

#endif /* WAVE_H_ */
