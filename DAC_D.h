#ifndef DAC_D_H_
#define DAC_D_H_
#include "Arduino.h"

/*
 * Initialize pins A0-A7 as output, this is the whole Port D
 */
void dac_setup();

void dac_out(uint8_t pins);

#endif /* DAC_D_H_ */
