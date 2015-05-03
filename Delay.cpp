#include "Delay.h"

// change step, like x1, x10, x100, x1000
static uint16_t step;
static uint32_t maxDelayNs;
static uint16_t delayNop;
static uint32_t calcDelayNs(uint16_t delay);
static void calcDelay(uint16_t step, boolean increase);
boolean delay_on;

uint16_t delay_reset() {
	step = 1;
	maxDelayNs = 0;
	delayNop = 0;
	delay_on = false;
	return step;
}

void delay_setMaxDelayNs(uint32_t _maxDelayNs) {
	maxDelayNs = _maxDelayNs;
}

void delay_wait() {
	// each iteration delays for 440 ns
	for (uint16_t i = 0; i < delayNop; i++) {
		NOP;
	}
}

static uint32_t calcDelayNs(uint16_t delay) {
	return (uint32_t) delay * DELAY_NOP_NS;
}

uint32_t delay_stepDelayNs() {
	return calcDelayNs(delayNop);
}

static void calcDelay(uint16_t step, boolean increase) {
	if (increase) {
		if (calcDelayNs(delayNop + step) <= maxDelayNs) {
			delayNop += step;
		}
	} else {
		if (delayNop > step) {
			delayNop -= step;
		} else {
			delayNop = 0;
		}
	}
	delay_on = delayNop > 0;
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

