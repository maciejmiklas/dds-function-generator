#include "LCD.h"

static LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

static void clcd(uint8_t row);
static void cleanRight(char *array, short from, short size);
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

	lcd.setCursor(5, row);
	lcd.print("Hz");

	lcd.setCursor(12, row);
	lcd.print("x");

	// row 1
	row = 1;
	clcd(row);
	lcd.setCursor(14, row);
	lcd.print("ns");
}

static void cleanRight(char *array, short from, short size) {
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

	cleanRight(buf, chars, size);
	lcd.print(buf);
}

void lcd_printFreqStep(uint16_t freqStep) {
	print(13, 0, 3, "%-03d", freqStep);
}

void lcd_printFreq(Frequency* freq) {
	print(0, 0, 5, "%5lu", freq->freq);

	// time in nanos in row 1
	char buf[14];
	util_flong_rigth(freq->fullPeriodNs, buf, 14);
	lcd.setCursor(1, 1);
	lcd.print(buf);
}

void lcd_printWave(WaveDef wave) {
	const char* waveStr;

	switch (wave) {

	case SQUARE_10:
		waveStr = "S10";
		break;

	case SQUARE_20:
		waveStr = "S20";
		break;

	case SQUARE_30:
		waveStr = "S30";
		break;

	case SQUARE_50:
		waveStr = "S50";
		break;

	case SQUARE_70:
		waveStr = "S70";
		break;

	case SAW:
		waveStr = "SAW";
		break;

	case SINE:
		waveStr = "SIN";
		break;

	case SINE_MAX:
		waveStr = "SIM";
		break;

	default:
		waveStr = "???";
		break;
	}

	lcd.setCursor(8, 0);
	lcd.print(waveStr);
}

