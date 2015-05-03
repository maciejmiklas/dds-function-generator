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
#define SQUARE_PERIOD_NS ((uint32_t) WAVE_SQUARE_STEP_NS * SQUARE_TABLE_SIZE)

#define SAW_TABLE_SIZE 2
static uint8_t SAW_TABLE[SAW_TABLE_SIZE] = { 0x00, 0x0F  };
#define SAW_PERIOD_NS ((uint32_t) WAVE_SAW_STEP_NS * SAW_TABLE_SIZE)

#define SEC_TO_NS 1000000000UL

static uint8_t *tablePointer;
static uint8_t *tableStart;
static uint8_t tableIdx;
static uint8_t tableSize;
static Frequency* frequency;
static uint32_t periodNs;

static void setSine();
static void setSquare();
static void setSaw();

void wave_setup() {
	frequency = (Frequency*) malloc(sizeof(Frequency));
}

Frequency* wave_frequencyChange(uint32_t stepDelayNs) {
	frequency->fullPeriodNs = periodNs + stepDelayNs * tableSize;
	frequency->freq = SEC_TO_NS / frequency->fullPeriodNs;
	return frequency;
}

uint32_t wave_calcMaxstepDelayNs() {
	return (MAX_CYCLE_TIME_NS - periodNs) / tableSize;
}

Frequency* wave_changeWave(WaveDef wave) {
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

	tableStart = tablePointer;
	tableIdx = 0;

	return wave_frequencyChange(0);
}

static void setSine() {
	tableSize = SIN_TABLE_SIZE;
	tablePointer = &SIN_TABLE[0];
	periodNs = SINE_PERIOD_NS;
}

static void setSquare() {
	tableSize = SQUARE_TABLE_SIZE;
	tablePointer = &SQUARE_TABLE[0];
	periodNs = SQUARE_PERIOD_NS;
}

static void setSaw() {
	tableSize = SAW_TABLE_SIZE;
	tablePointer = &SAW_TABLE[0];
	periodNs = SAW_PERIOD_NS;
}

uint8_t wave_next() {
	tableIdx++;
	if (tableIdx == tableSize) {
		tableIdx = 0;
		tablePointer = tableStart;
	}
	return *tablePointer++;
}
