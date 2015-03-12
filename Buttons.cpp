#include "Buttons.h"
#include "LCD.h"

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

static void pciSetup(byte pin) {
	*digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin));  // enable pin
	PCIFR |= bit(digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
	PCICR |= bit(digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

void btn_setup() {
	lcd.begin(16, 2);
	lcd.noAutoscroll();

	for (int i = A0; i <= A3; i++) {
		pinMode(i, INPUT);   // set Pin as Input (default)
		digitalWrite(i, HIGH);  // enable pullup resistor
		pciSetup(i);
	}
}

ISR (PCINT1_vect) {
	lcd.setCursor(0, 0);

	lcd.print(digitalRead(A0));
	lcd.print("-");

	lcd.print(digitalRead(A1));
	lcd.print("-");

	lcd.print(digitalRead(A2));
	lcd.print("-");

	lcd.print(digitalRead(A3));
}

