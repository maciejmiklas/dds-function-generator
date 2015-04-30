#include "Wave.h"

#define SIN_TABLE_SIZE 119
static uint8_t SIN_TABLE[SIN_TABLE_SIZE] = { 0x80, 0x86, 0x8D, 0x93, 0x9A, 0xA0, 0xA7, 0xAD, 0xB3, 0xB9, 0xBF, 0xC5,
		0xCA, 0xD0, 0xD5, 0xDA, 0xDE, 0xE3, 0xE7, 0xEA, 0xEE, 0xF1, 0xF4, 0xF7, 0xF9, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF,
		0xFF, 0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xF9, 0xF7, 0xF4, 0xF1, 0xEE, 0xEA, 0xE7, 0xE3, 0xDE, 0xDA, 0xD5, 0xD0,
		0xCA, 0xC5, 0xBF, 0xB9, 0xB3, 0xAD, 0xA7, 0xA0, 0x9A, 0x93, 0x8D, 0x86, 0x80, 0x79, 0x72, 0x6C, 0x65, 0x5F,
		0x58, 0x52, 0x4C, 0x46, 0x40, 0x3A, 0x35, 0x2F, 0x2A, 0x25, 0x21, 0x1C, 0x18, 0x15, 0x11, 0xE, 0xB, 0x8, 0x6,
		0x4, 0x3, 0x2, 0x1, 0x0, 0x1, 0x2, 0x3, 0x4, 0x6, 0x8, 0xB, 0xE, 0x11, 0x15, 0x18, 0x1C, 0x21, 0x25, 0x2A, 0x2F,
		0x35, 0x3A, 0x40, 0x46, 0x4C, 0x52, 0x58, 0x5F, 0x65, 0x6C, 0x72, 0x79, 0x7F };
// time for single sine cycle assuming delay in main loop is zero
#define SINE_PERIOD_NS ((uint32_t) WAVE_SIN_STEP_NS * SIN_TABLE_SIZE)

#define SQUARE_TABLE_SIZE 2
static uint8_t SQUARE_TABLE[SQUARE_TABLE_SIZE] = { 0x00, 0xFF };

#define SAW_TABLE_SIZE 1
static uint8_t SAW_TABLE[SAW_TABLE_SIZE] = { 0x00 };

#define SEC_TO_NS 1000000000UL

static uint8_t *tablePointer;
static uint8_t tableIdx;
static uint8_t tableSize;
static Frequency* frequency;
static uint32_t periodNs;
static uint8_t steps;

static void setSine();
static void setSquare();
static void setSaw();

Frequency* wave_setup(uint32_t stepDelayNs, Waves wave) {
	wave_changeWave(wave);

	frequency = (Frequency*) malloc(sizeof(Frequency));
	wave_frequencyChange(stepDelayNs);
	return frequency;
}

Frequency* wave_frequencyChange(uint32_t stepDelayNs) {
	frequency->fullPeriodNs = periodNs + stepDelayNs * steps;
	frequency->freq = SEC_TO_NS / frequency->fullPeriodNs;
	return frequency;
}

uint32_t wave_calcMaxstepDelayNs() {
	return (MAX_CYCLE_TIME_NS - periodNs) / steps;
}

void wave_changeWave(Waves wave) {
	switch (wave) {

	case SQUARE:
		setSquare();
		break;

	case SAW:
		setSaw();
		break;

	case SINE:
	default:
		setSine();
		break;
	}
}

static void setSine() {
	tableSize = SIN_TABLE_SIZE;
	tableIdx = 0;
	tablePointer = &SIN_TABLE[0];
	periodNs = SINE_PERIOD_NS;
	steps = SIN_TABLE_SIZE;
}

static void setSquare() {
	tableSize = SIN_TABLE_SIZE;
	tableIdx = 0;
	tablePointer = &SQUARE_TABLE[0];
	periodNs = 0; //TODO
	steps = 0; //TODO
}

static void setSaw() {
	tableSize = SAW_TABLE_SIZE;
	tableIdx = 0;
	tablePointer = &SAW_TABLE[0];
	periodNs = 0; //TODO
	steps = 0; //TODO
}

uint8_t wave_next() {
	tableIdx++;
	if (tableIdx == tableSize) {
		tableIdx = 0;
		tablePointer = &SQUARE_TABLE[0];
	}
	return *tablePointer++;
}
