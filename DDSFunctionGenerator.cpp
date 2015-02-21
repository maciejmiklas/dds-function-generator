#include "DDSFunctionGenerator.h"

void setup() {
	log_setup();
	dac_setup();
	//wave_setSine();

	dac_out(B00000001);
}

void loop() {
	//uint8_t outVal = wave_next();
	//dac_out(outVal);
}
