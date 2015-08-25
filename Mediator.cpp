#include "Mediator.h"

static byte curentWave = SINE;
static void updateFreq(uint32_t stepDelayNs);
static void setupMaxStepDelay();
static void setWave(WaveDef wave);

void mediator_setup() {
	lcd_setup();
	btn_setup();
	dac_setup();
	wave_setup();

	setWave(static_cast<WaveDef>(curentWave));
}

static void setWave(WaveDef wave) {
	uint16_t step = delay_reset();
	Frequency* freq = wave_changeWave(wave);
	setupMaxStepDelay();
	lcd_printFreqStep(step);
	lcd_printFreq(freq);
	lcd_printWave(wave);
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
	if (curentWave == _LAST) {
		curentWave = _FIRST;
	} else {
		curentWave++;
	}
	setWave(static_cast<WaveDef>(curentWave));
}

static void updateFreq(uint32_t stepDelayNs) {
	Frequency* freq = wave_frequencyChange(stepDelayNs);
	lcd_printFreq(freq);
}

static void setupMaxStepDelay() {
	uint32_t maxDelayNs = wave_calcMaxstepDelayNs();
	delay_setMaxDelayNs(maxDelayNs);
}
