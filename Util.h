#ifndef DOMAIN_H_
#define DOMAIN_H_

#include "Arduino.h"

uint16_t util_freeRam();

/* formats long aligning it to the right side of the array.*/
void util_flong_rigth(int32_t val, char* buf, uint8_t destSize);

#endif /* DOMAIN_H_ */
