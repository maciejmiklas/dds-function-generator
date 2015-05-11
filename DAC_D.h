#ifndef DAC_D_H_
#define DAC_D_H_
#include "Arduino.h"

/*
 * Initialize pins D0-D7 as output, this is the whole Port D
 *
 * Mapping between bit set and voltage on output (voltage divider with: 1,5k-750ohm):
 * B00000001 -  22 mV
 * B00000010 -  38 mV
 * B00000100 -  73 mV
 * B00001000 -  140 mV
 * B00010000 -  276 mV
 * B00100000 -  545 mV
 * B01000000 -  1.08 V
 * B10000000 -  2.18 V
 *
 * B00000001 - 22 mV
 * B00000011 - 56 mV
 * B00000111 - 125 mV
 * B00001111 - 265 mV
 * B00011111 - 543 mV
 * B00111111 - 1.1 V
 * B01111111 - 2.23 V
 * B11111111 - 4.47 V
 */
void dac_setup();

void dac_out(uint8_t pins);

#endif /* DAC_D_H_ */
