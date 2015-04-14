#include "Buttons.h"
#include "LCD.h"
#include "Delay.h"
#include "Wave.h"

#define SEC_TO_NS 1000000000UL

static volatile uint32_t pressMs = 0;

static void pciSetup(byte pin) {
	*digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin));  // enable pin
	PCIFR |= bit(digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
	PCICR |= bit(digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

static void updateFrequency() {
	uint32_t constPeriodNs = wave_constPeriodNs();
	uint8_t steps = wave_steps();
	uint32_t waitNs = delay_waitNs();
	uint32_t fullPeriodNs = constPeriodNs + waitNs * steps;
	uint16_t freq = SEC_TO_NS / fullPeriodNs;

	lcd_printFreq(fullPeriodNs, freq);
}

void btn_setup() {
	for (int i = A0; i <= A3; i++) {
		pinMode(i, INPUT);   // set Pin as Input (default)
		digitalWrite(i, HIGH);  // enable pullup resistor
		pciSetup(i);
	}

	updateFrequency();
}

ISR (PCINT1_vect) {
	uint32_t ms = millis();
	if (ms - pressMs < PRESS_MS) {
		return;
	}

	pressMs = ms;
	if (digitalRead(A0) == 0) {
		delay_up();
		updateFrequency();

	} else if (digitalRead(A1) == 0) {
		delay_down();
		updateFrequency();

	} else if (digitalRead(A2) == 0) {
		delay_step();

	} else if (digitalRead(A3) == 0) {

	}
}

