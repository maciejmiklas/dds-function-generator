#ifndef DAC_D_H_
#define DAC_D_H_
#include "Arduino.h"

/*
 * Initialize pins A0-A7 as output, this is the whole Port D
 *
 * Mapping between bit set and voltage on output (voltage divider with: 1k-510 ohm):
 * B00000001 - 30.8 mV
 * B00000010 - 46.4 mV
 * B00000100 - 80.6 mV
 * B00001000 - 153.4 mV
 * B00010000 - 300.1 mV
 * B00100000 - 590 mV
 * B01000000 - 1.171 V
 * B10000000 - 2.34 V
 *
 * B00000001 - 30.8 mV
 * B00000011 - 72.5 mV
 * B00000111 - 148.5 mV
 * B00001111 - 297.2 mV
 * B00011111 - 593 mV
 * B00111111 - 1.18 V
 * B01111111 - 2.349 V
 * B11111111 - 4.7 V
 */
void dac_setup();

void dac_out(uint8_t pins);

#endif /* DAC_D_H_ */
