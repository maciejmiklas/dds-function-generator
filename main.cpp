#include <Arduino.h>
#include "Mediator.h"

//Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (*func)()) {
	return 0;
}

int main(void) {
	init();

#if defined(USBCON)
	USBDevice.attach();
#endif

	mediator_setup();
	uint16_t tableIdx = 0;
	wave_tablePointer = wave_tableStart;

	while (true) {
		PORTD = *(wave_tablePointer + tableIdx);
		if (wave_delayOn) {
			wave_wait();
		}

		tableIdx++;
		if (tableIdx == wave_tableSize) {
			wave_tablePointer = wave_tableStart;
			tableIdx = 0;
		}
	}

	return 0;
}

