#include "DDSFunctionGenerator.h"

boolean sw = false;

void setup() {
	lcd_setup();
	dac_setup();
	delay_setup();
	uint32_t stepDelayNs = delay_stepDelayNs();
	wave_setup(stepDelayNs);
	btn_setup();
}

void loop() {
	uint8_t outVal = wave_next();
	dac_out(outVal);
	delay_wait();
}
