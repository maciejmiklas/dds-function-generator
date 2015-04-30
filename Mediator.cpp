#include "Mediator.h"

static void updateFreq(uint32_t stepDelayNs);
static void setupMaxStepDelay();

void mediator_setup() {
	lcd_setup();
	dac_setup();
	uint16_t step = delay_setup();
	lcd_printFreqStep(step);
	setupMaxStepDelay();

	uint32_t stepDelayNs = delay_stepDelayNs();
	wave_setup(stepDelayNs, SINE);
	btn_setup();
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
