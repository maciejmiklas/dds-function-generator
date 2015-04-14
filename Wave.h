#ifndef WAVE_H_
#define WAVE_H_

#include "Arduino.h"
#include "Delay.h"

// time for single step of sine wave. Single period consists of #SIN_TABLE_SIZE steps
#define WAVE_SIN_STEP_NS 4273UL

void wave_setSine();
void wave_setSquare();
void wave_setSaw();
uint8_t wave_next();
uint8_t wave_steps();
void wave_printFrequency();
void wave_printFrequency();
void wave_setup();
#endif /* WAVE_H_ */
