#ifndef WAVE_H_
#define WAVE_H_

#include "Arduino.h"

// time for single step of sine wave. Single period consists of #SIN_TABLE_SIZE steps
#define WAVE_SIN_STEP_NS 4273UL
#define WAVE_SQUARE_STEP_NS 1UL //TODO
#define WAVE_SAW_STEP_NS 1UL //TODO

// cycle cannot take longer than 2^32 ns
#define MAX_CYCLE_TIME_NS 2147483648UL

extern uint8_t *wave_tablePointer;
extern uint8_t *wave_tableStart;
extern uint8_t wave_tableIdx;
extern uint8_t wave_tableSize;

typedef struct {
	uint32_t fullPeriodNs;
	uint16_t freq;
} Frequency;

enum WaveDef {
	SINE = 0, SQUARE = 1, SAW = 2
};

Frequency* wave_changeWave(WaveDef wave);
uint32_t wave_calcMaxstepDelayNs();
Frequency* wave_frequencyChange(uint32_t stepDelayNs);
void wave_setup();

#endif /* WAVE_H_ */
