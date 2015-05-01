#ifndef WAVE_H_
#define WAVE_H_

#include "Arduino.h"
#include "Log.h"

// time for single step of sine wave. Single period consists of #SIN_TABLE_SIZE steps
#define WAVE_SIN_STEP_NS 4273UL

// cycle cannot take longer than 2^32 ns
#define MAX_CYCLE_TIME_NS 2147483648UL

typedef struct {
	uint32_t fullPeriodNs;
	uint16_t freq;
} Frequency;

enum Waves {
	SINE, SQUARE, SAW
};

void wave_changeWave(Waves wave);
uint8_t wave_next();
uint32_t wave_calcMaxstepDelayNs();
Frequency* wave_frequencyChange(uint32_t stepDelayNs);
Frequency* wave_setup(uint32_t stepDelayNs, Waves wave);

#endif /* WAVE_H_ */
