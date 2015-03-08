#include "DAC_D.h"

void dac_setup() {
	DDRD = B11111111;
	PORTD = B00000000;
}

void dac_out(uint8_t pins) {
	PORTD = pins;
}
