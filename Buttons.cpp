#include "Buttons.h"

static volatile uint32_t pressMs = 0;
static void pciSetup(byte pin);

static void pciSetup(byte pin) {
	*digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin));  // enable pin
	PCIFR |= bit(digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
	PCICR |= bit(digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

void btn_setup() {
	for (int i = A0; i <= A3; i++) {
		pinMode(i, INPUT);   // set Pin as Input (default)
		digitalWrite(i, HIGH);  // enable pullup resistor
		pciSetup(i);
	}
}

ISR (PCINT1_vect) {
	uint32_t ms = millis();
	if (ms - pressMs < PRESS_MS) {
		return;
	}
	if (digitalRead(A0) == 0) {
		mediator_onDelayDown();

	} else if (digitalRead(A1) == 0) {
		mediator_onDelayUp();

	} else if (digitalRead(A2) == 0) {
		mediator_onDelayStep();

	} else if (digitalRead(A3) == 0) {
		mediator_onWaveNext();
	}

	pressMs = ms;
}

