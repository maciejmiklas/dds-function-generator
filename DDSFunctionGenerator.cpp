#include "DDSFunctionGenerator.h"

boolean sw = false;

void setup() {
	dac_setup();
	wave_setSine();
	lcd_setup();
	btn_setup();
}

void loop() {
	uint8_t outVal = wave_next();
	dac_out(outVal);
	delay_loop();
}
