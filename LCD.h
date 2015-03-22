#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>
#include <LiquidCrystal.h>

void lcd_setup();
void lcd_ln(uint8_t row, const char *fmt, ...);

#endif /* LCD_H_ */
