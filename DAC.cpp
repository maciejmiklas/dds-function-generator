#include "DAC.h"

void dac_setup() {
	DDRD = B11111111;
}

void dac_out(uint8_t pins) {
	PORTD = pins;
}
