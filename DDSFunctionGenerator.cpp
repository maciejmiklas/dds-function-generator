#include "DDSFunctionGenerator.h"

boolean sw = false;

void setup() {
	log_setup();
	dac_setup();
	wave_setSine();
}

void loop() {
	uint8_t outVal = wave_next();
	dac_out(outVal);
}
