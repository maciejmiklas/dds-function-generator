#ifndef LCD_H_
#define LCD_H_

#include <LiquidCrystal.h>
#include <Arduino.h>

void lcd_setup();
void lcd_ln(uint8_t row, char str[]);

#endif /* LCD_H_ */
