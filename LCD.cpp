#include "LCD.h"

static LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

static void clcd(uint8_t row) {
	lcd.setCursor(0, row);
	lcd.print("                ");
	lcd.setCursor(0, row);
}

void lcd_setup() {
	lcd.begin(16, 2);
	lcd.noAutoscroll();
	// row 0
	clcd(0);

	// row 1
	clcd(1);
	lcd.print("Step:");
}

static void lcd_ln(uint8_t row, const char *fmt, ...) {
	clcd(row);

	char buf[17];
	va_list va;
	va_start(va, fmt);
	vsprintf(buf, fmt, va);
	va_end(va);

	lcd.print(buf);
}

static void padRight(char *array, short from, short size) {
	for (short int i = from; i < size; i++) {
		array[i] = ' ';
	}
}

void lcd_printFreqStep(uint16_t reqStep) {
	lcd.setCursor(5, 1);
	char buf[7];
	short chars = sprintf(buf, "%-dus", reqStep);
	padRight(buf, chars, 7);
	lcd.print(buf);
}

void lcd_printFreq(int32_t reqStep) {
	lcd.setCursor(0, 0);
	char buf[17];
	sprintf(buf, "%-15lu", reqStep);
	lcd.print(buf);
}
