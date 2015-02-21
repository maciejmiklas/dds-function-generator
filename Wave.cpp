#include "DAC.h"

#define SIN_TABLE_SIZE 181
static uint8_t  SIN_TABLE[SIN_TABLE_SIZE] = { 0x80, 0x84, 0x88, 0x8D, 0x91,
		0x96, 0x9A, 0x9E, 0xA3, 0xA7, 0xAB, 0xAF, 0xB3, 0xB7, 0xBB, 0xBF, 0xC3,
		0xC7, 0xCA, 0xCE, 0xD1, 0xD5, 0xD8, 0xDB, 0xDE, 0xE1, 0xE4, 0xE7, 0xE9,
		0xEC, 0xEE, 0xF0, 0xF2, 0xF4, 0xF6, 0xF7, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD,
		0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFD, 0xFC, 0xFB,
		0xFA, 0xF9, 0xF7, 0xF6, 0xF4, 0xF2, 0xF0, 0xEE, 0xEC, 0xE9, 0xE7, 0xE4,
		0xE1, 0xDE, 0xDB, 0xD8, 0xD5, 0xD1, 0xCE, 0xCA, 0xC7, 0xC3, 0xBF, 0xBB,
		0xB7, 0xB3, 0xAF, 0xAB, 0xA7, 0xA3, 0x9E, 0x9A, 0x96, 0x91, 0x8D, 0x88,
		0x84, 0x80, 0x7B, 0x77, 0x72, 0x6E, 0x69, 0x65, 0x61, 0x5C, 0x58, 0x54,
		0x50, 0x4C, 0x48, 0x44, 0x40, 0x3C, 0x38, 0x35, 0x31, 0x2E, 0x2A, 0x27,
		0x24, 0x21, 0x1E, 0x1B, 0x18, 0x16, 0x13, 0x11, 0xF, 0xD, 0xB, 0x9, 0x8,
		0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1,
		0x2, 0x3, 0x4, 0x5, 0x6, 0x8, 0x9, 0xB, 0xD, 0xF, 0x11, 0x13, 0x16,
		0x18, 0x1B, 0x1E, 0x21, 0x24, 0x27, 0x2A, 0x2E, 0x31, 0x35, 0x38, 0x3C,
		0x40, 0x44, 0x48, 0x4C, 0x50, 0x54, 0x58, 0x5C, 0x61, 0x65, 0x69, 0x6E,
		0x72, 0x77, 0x7B, 0x7F };

#define SQUARE_TABLE_SIZE 1
static uint8_t SQUARE_TABLE[SQUARE_TABLE_SIZE] = { 0x80 };

#define SAW_TABLE_SIZE 1
static uint8_t SAW_TABLE[SAW_TABLE_SIZE] = { 0x80 };

static uint8_t *tablePointer;
static uint8_t tableIdx;
static uint8_t tableSize;

void wave_setSine() {
	tableSize = SIN_TABLE_SIZE;
	tableIdx = 0;
	tablePointer = &SIN_TABLE[0];
}

void wave_setSquare() {
	tableSize = SIN_TABLE_SIZE;
	tableIdx = 0;
	tablePointer = &SQUARE_TABLE[0];
}

void wave_setSaw() {
	tableSize = SAW_TABLE_SIZE;
	tableIdx = 0;
	tablePointer = &SAW_TABLE[0];
}

uint8_t wave_next() {
	tableIdx++;
	if (tableIdx == tableSize) {
		tableIdx = 0;
	}
	// TODO test speed
	//return tablePointer[tableIdx];
	return *tablePointer++;
}

