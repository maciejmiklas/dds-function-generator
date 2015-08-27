#include "Mediator.h"

static void printWave(Frequency* freq);

void mediator_setup() {
	lcd_setup();
	btn_setup();
	dac_setup();
	Frequency* freq =  wave_setup();
	printWave(freq);
}

static void printWave(Frequency* freq) {
	lcd_printFreqStep(freq->delayStep);
	lcd_printFreq(freq);
	lcd_printWave(freq->wave);
}

void mediator_onDelayUp() {
	Frequency* freq = wave_delayUp();
	lcd_printFreq(freq);
}

void mediator_onDelayDown() {
	Frequency* freq = wave_delayDown();
	lcd_printFreq(freq);
}

void mediator_onDelayStep() {
	uint16_t step = wave_delayNextStep();
	lcd_printFreqStep(step);
}

void mediator_onWaveNext() {
	Frequency* freq =  wave_netxWave();
	printWave(freq);
}
