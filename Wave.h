#ifndef WAVE_H_
#define WAVE_H_

#include "LCD.h"
#include "Arduino.h"

// time for single step of sine wave. Single period consists of #SIN_TABLE_SIZE steps
#define WAVE_SIN_STEP_NS 4273UL

void wave_setSine();
void wave_setSquare();
void wave_setSaw();
uint8_t wave_next();
uint8_t wave_steps();
void wave_frequencyChange(uint32_t stepDelayNs);
void wave_setup(uint32_t stepDelayNs);

#endif /* WAVE_H_ */
