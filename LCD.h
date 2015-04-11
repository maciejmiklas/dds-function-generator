#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>
#include <LiquidCrystal.h>

void lcd_setup();
void lcd_printFreqStep(uint16_t reqStep);
void lcd_printFreq(int32_t reqStep);

#endif /* LCD_H_ */
