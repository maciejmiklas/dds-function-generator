#include "Mediator.h"

static byte curentWave = SINE;
static void updateFreq(uint32_t stepDelayNs);
static void changeWave(WaveDef wave);

void mediator_setup() {
	lcd_setup();
	btn_setup();
	dac_setup();
	wave_setup();

	changeWave(static_cast<WaveDef>(curentWave));
}

static void changeWave(WaveDef wave) {
	wave_changeWave(wave);

	uint16_t initDelayNop = wave_getInitDelayNop();
	delay_setup(wave_calcMaxstepDelayNs(), initDelayNop);
	Frequency* freq = wave_frequencyChange(delay_calcDelayNs(initDelayNop));

	lcd_printFreqStep(1);
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
	changeWave(static_cast<WaveDef>(curentWave));
}

static void updateFreq(uint32_t stepDelayNs) {
	Frequency* freq = wave_frequencyChange(stepDelayNs);
	lcd_printFreq(freq);
}

