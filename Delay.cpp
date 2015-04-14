#include "Delay.h"

// 1852 Hz, 540us pro step
static uint16_t delayNop = 0;
static uint16_t step = 1;

void delay_setup() {
	lcd_printFreqStep(step);
}

void delay_wait() {
	// each iteration delays for 440 ns
	for (uint16_t i = 0; i < delayNop; i++) {
		NOP;
	}
}

uint32_t delay_waitNs() {
	return (uint32_t) delayNop * DELAY_NOP_NS;
}

static void calcDelay(uint16_t step, boolean increase) {
	if (increase) {
		delayNop += step;
	} else {
		if (delayNop > step) {
			delayNop -= step;
		} else {
			delayNop = 0;
		}
	}
	lcd_printSteps(delayNop);
}
void delay_step() {
	step *= 10;
	if (step > DELAY_FREQ_STEP_MAX) {
		step = 1;
	}
	lcd_printFreqStep(step);
}

void delay_up() {
	calcDelay(step, true);
}

void delay_down() {
	calcDelay(step, false);
}

