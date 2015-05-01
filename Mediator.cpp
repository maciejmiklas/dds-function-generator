#include "Mediator.h"

static void updateFreq(uint32_t stepDelayNs);
static void setupMaxStepDelay();

void mediator_setup() {
	lcd_setup();
	btn_setup();
	dac_setup();
	uint16_t step = delay_setup();
	uint32_t stepDelayNs = delay_stepDelayNs();
	Frequency* freq = wave_setup(stepDelayNs, SINE);
	setupMaxStepDelay();
	lcd_printFreqStep(step);
	lcd_printFreq(freq);
}

void mediator_loop() {
	uint8_t outVal = wave_next();
	dac_out(outVal);
	delay_wait();
}

void mediator_onDelayUp() {
	uint32_t stepDelayNs = delay_up();
	updateFreq(stepDelayNs);
}

void mediator_onDelayDown() {
	uint32_t stepDelayNs = delay_down();
	updateFreq(stepDelayNs);
}

void mediator_onDelayStep() {
	uint16_t step = delay_nextStep();
	lcd_printFreqStep(step);
}

void mediator_onWaveNext() {
	//TODO implement
	setupMaxStepDelay();
}

static void updateFreq(uint32_t stepDelayNs) {
	Frequency* freq = wave_frequencyChange(stepDelayNs);
	lcd_printFreq(freq);
}

static void setupMaxStepDelay() {
	uint32_t maxDelayNs = wave_calcMaxstepDelayNs();
	delay_setMaxDelayNs(maxDelayNs);
}
