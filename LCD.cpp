#include "LCD.h"

static LiquidCrystal lcd(13, 12,11, 10, 9, 8);

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
}

void lcd_ln(uint8_t row, char str[]) {
	lcd.setCursor(0, row);
	lcd.print(str);
}
