#include "LCD.h"

static LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

static void clcd(uint8_t row);
static void padRight(char *array, short from, short size);
static void print(uint8_t col, uint8_t row, uint8_t size, const char *fmt, ...);

static void clcd(uint8_t row) {
	lcd.setCursor(0, row);
	lcd.print("                ");
	lcd.setCursor(0, row);
}

void lcd_setup() {
	lcd.begin(16, 2);
	lcd.noAutoscroll();
	// row 0
	uint8_t row = 0;
	clcd(row);

	lcd.setCursor(6, row);
	lcd.print("Hz");

	lcd.setCursor(12, row);
	lcd.print("x");

	// row 1
	row = 1;
	clcd(row);

	lcd.setCursor(14, row);
	lcd.print("ns");
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
	print(13, 0, 3, "%-03d", freqStep);
}

void lcd_printFreq(Frequency* freq) {
	print(0, 0, 6, "%6d", freq->freq);
	print(4, 1, 10, "%10lu", freq->fullPeriodNs);
}

void lcd_printWave(WaveDef wave) {
	const char* waveStr;

	switch (wave) {

	case SQUARE:
		waveStr = "SQR";
		break;

	case SAW:
		waveStr = "SAW";
		break;

	case SINE:
		waveStr = "SIN";
		break;

	default:
		waveStr = "???";
		break;
	}

	lcd.setCursor(8, 0);
	lcd.print(waveStr);
}
