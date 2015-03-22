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
	lcd.print("HI !");
}

void lcd_ln(uint8_t row, const char *fmt, ...) {
	clcd(row);

	char buf[17];
	va_list va;
	va_start(va, fmt);
	vsprintf(buf, fmt, va);
	va_end(va);

	lcd.print(buf);
}
