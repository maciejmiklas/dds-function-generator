#include "Buttons.h"
#include "LCD.h"
#include "Delay.h"
#include "Wave.h"

static volatile uint32_t pressMs = 0;

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

	pressMs = ms;
	if (digitalRead(A0) == 0) {
		delay_up();
		wave_printFrequency();

	} else if (digitalRead(A1) == 0) {
		delay_down();
		wave_printFrequency();

	} else if (digitalRead(A2) == 0) {
		delay_step();

	} else if (digitalRead(A3) == 0) {

	}
}

