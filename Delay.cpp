#include "Delay.h"

static int32_t delayMic = 0;
static uint8_t steep = 1;

static int32_t cnt = 0;

static void check() {
	if (delayMic < 0) {
		delayMic = 0;
	}
	lcd_ln(0, "%d", delayMic);
	lcd_ln(1, "%d", cnt++);
}

void delay_loop() {
	if (delayMic > 0) {
		delayMicroseconds(delayMic);
	}
}

void delay_step_up() {
	//check();
}

void delay_step_down() {
	//check();
}

void delay_freq_up() {
	delayMic += steep;
	check();
}

void delay_freq_down() {
	delayMic -= steep;
	check();
}

