#include "DDSFunctionGenerator.h"

void setup() {
	mediator_setup();
}

void loop() {
	uint8_t outVal = wave_next();
	dac_out(outVal);
	delay_wait();
}
