#include "DDSFunctionGenerator.h"

boolean sw = false;

void setup() {
	dac_setup();
	wave_setSine();
	//dac_out(B00000001);
}

void loop() {
	uint8_t outVal = wave_next();
	dac_out(outVal);
	//delay(1);
}
