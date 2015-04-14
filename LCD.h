#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Delay.h"

void lcd_setup();
void lcd_printFreqStep(uint16_t reqStep);
void lcd_printSteps(uint16_t steps);
void lcd_printFreq(uint32_t fullPeriodMicros, uint16_t freq);

#endif /* LCD_H_ */
