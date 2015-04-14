#ifndef WAVE_H_
#define WAVE_H_

#include "Arduino.h"

// time for single step of sine wave. Single period consists of #SIN_TABLE_SIZE steps
#define WAVE_SIN_STEP_NS 4000UL

void wave_setSine();
void wave_setSquare();
void wave_setSaw();
uint8_t wave_next();
uint32_t wave_constPeriodNs();
uint8_t wave_steps();

#endif /* WAVE_H_ */
