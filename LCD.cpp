#include "LCD.h"

#define CH_MICRO 228
#define CH_PI 247

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
	lcd.print("    Hz     x");

	// row 1
	clcd(1);
	lcd.print("           s/2");

	lcd.setCursor(10, 1);
	lcd.print((char)CH_MICRO);

	lcd.setCursor(14, 1);
	lcd.print((char)CH_PI);
}

static void padRight(char *array, short from, short size) {
	for (short int i = from; i < size; i++) {
		array[i] = ' ';
	}
	array[size] = '\0';
}

static void print(uint8_t col, uint8_t row, uint8_t size, const char *fmt, ...) {
	lcd.setCursor(col, row);

	char buf[size + 1];
	va_list va;
	va_start(va, fmt);
	short chars = vsprintf(buf, fmt, va);
	va_end(va);

	padRight(buf, chars, size);
	lcd.print(buf);
}

void lcd_printFreqStep(uint16_t freqStep) {
	print(12, 0, 4, "%-04d", freqStep);
}

void lcd_printFreq(uint32_t fullPeriodMicros, uint16_t freq) {
	print(0, 0, 4, "%4d", freq);
	print(0, 1, 10, "%10lu", fullPeriodMicros);
}
