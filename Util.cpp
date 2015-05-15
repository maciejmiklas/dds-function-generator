#include "Util.h"

uint16_t util_freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (uint16_t) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void util_flong_rigth(int32_t val, char* buf, uint8_t destSize) {
	int8_t sizeCnt = destSize;

	*(buf + --sizeCnt) = 0; // Null terminate the scratch buffer

	if (val == 0) {
		*(buf + --sizeCnt) = '0';

	} else {
		boolean neg = (val < 0);
		// Work with positive values from here on
		if (val < 0) {
			val = -val;
		}

		// work from end of the buffer
		int groupCnt = 3;

		while (val != 0) {
			int digit = val % 10;
			val = val / 10;

			*(buf + --sizeCnt) = "0123456789"[digit];

			if ((val != 0) && (--groupCnt == 0)) {
				*(buf + --sizeCnt) = ',';
				groupCnt = 3;
			}
		}

		if (neg) {
			*(buf + --sizeCnt) = '-';
		}
	}

	// fill up remaining characters of the buffer with spaces
	for (sizeCnt--; sizeCnt >= 0; sizeCnt--) {
		*(buf + sizeCnt) = ' ';
	}
}

