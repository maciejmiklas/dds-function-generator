#include "Delay.h"

static uint16_t delayNop = 0;
static uint16_t step = 1;
static uint32_t maxDelayNs = 0;

static uint32_t calcDelayNs(uint16_t delayNop);
static void calcDelay(uint16_t step, boolean increase);

void delay_setMaxDelayNs(uint32_t _maxDelayNs) {
	maxDelayNs = _maxDelayNs;
}

uint16_t delay_setup() {
	return step;
}

void delay_wait() {
	// each iteration delays for 440 ns
	for (uint16_t i = 0; i < delayNop; i++) {
		NOP;
	}
}

static uint32_t calcDelayNs(uint16_t delayNop) {
	return (uint32_t) delayNop * DELAY_NOP_NS;
}

uint32_t delay_stepDelayNs() {
	return calcDelayNs(delayNop);
}

static void calcDelay(uint16_t step, boolean increase) {
	if (increase && calcDelayNs(delayNop + step) <= maxDelayNs) {
		delayNop += step;
	} else {
		if (delayNop > step) {
			delayNop -= step;
		} else {
			delayNop = 0;
		}
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
	calcDelay(step, true);
	return delay_stepDelayNs();
}

uint32_t delay_down() {
	calcDelay(step, false);
	return delay_stepDelayNs();
}

