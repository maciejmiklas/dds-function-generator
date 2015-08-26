#include "Delay.h"

// change step, like x1, x10, x100, x1000
static uint16_t step;
static uint32_t maxDelayNs;
static uint16_t initDelayNop;
static uint16_t delayNop;
boolean delayOn;

void delay_setup(uint32_t _maxDelayNs, uint16_t _initDelayNop) {
	step = 1;
	maxDelayNs = _maxDelayNs;
	initDelayNop = _initDelayNop;
	delayNop = _initDelayNop;
	delayOn = _initDelayNop > 0;
}

void delay_wait() {
	// each iteration delays for 440 ns
	for (uint16_t i = 0; i < delayNop; i++) {
		NOP;
	}
}

uint16_t delay_nextStep() {
	step *= 10;
	if (step > DELAY_FREQ_STEP_MAX) {
		step = 1;
	}
	return step;
}

uint32_t delay_up() {
	if (delay_calcDelayNs(delayNop + step) <= maxDelayNs) {
		delayNop += step;
	}

	delayOn = delayNop > 0;
	return delay_calcDelayNs(delayNop);
}

uint32_t delay_down() {
	if (delayNop > step) {
		delayNop -= step;
	} else {
		delayNop = initDelayNop;
	}

	delayOn = delayNop > 0;
	return delay_calcDelayNs(delayNop);
}

