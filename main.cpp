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
		wave_tablePointer = wave_tableStart;
		for (uint8_t tableIdx = 0; tableIdx < wave_tableSize; tableIdx++) {
			PORTD = *(wave_tablePointer + tableIdx);
			if (delay_on) {
				delay_wait();
			}
		}
	}

	return 0;
}

