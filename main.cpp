#include <Arduino.h>
#include "Mediator.h"
#include "Delay.h"

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

	while (true) {
		if (wave_tableIdx == wave_tableSize) {
			wave_tableIdx = 0;
			wave_tablePointer = wave_tableStart;
		} else {
			wave_tableIdx++;
			*wave_tablePointer++;
		}

		PORTD = *wave_tablePointer;

		if (delay_on) {
			delay_wait();
		}
	}

	return 0;
}

