#include "Delay.h"
// 1852 Hz, 540 us pro step
static uint32_t delayMic = 0;
static uint16_t step = 1;

void delay_loop() {
	if (delayMic > 0) {
		delayMicroseconds(delayMic);
	}
}

static void freq(uint16_t step, boolean increase) {
	if (increase) {
		delayMic += step;
	} else {
		if (delayMic > step) {
			delayMic -= step;
		} else {
			delayMic = 0;
		}
	}
	lcd_printFreq(delayMic);
}
void delay_freqStep() {
	step *= 10;
	if (step > FREQ_STEP_MAX) {
		step = 1;
	}
	lcd_printFreqStep(step);
}

void delay_freqUp() {
	freq(step, true);
}

void delay_freqDown() {
	freq(step, false);
}

