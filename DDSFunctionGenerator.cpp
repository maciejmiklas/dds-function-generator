#include "DDSFunctionGenerator.h"

boolean sw = false;

void setup() {
	lcd_setup();
	dac_setup();
	wave_setup();
	btn_setup();
	delay_setup();
}

void loop() {
	uint8_t outVal = wave_next();
	dac_out(outVal);
	delay_wait();
}
