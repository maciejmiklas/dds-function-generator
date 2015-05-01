#ifndef Mediator_H_
#define Mediator_H_

#include "Arduino.h"
#include "DAC_D.h"
#include "Wave.h"
#include "LCD.h"
#include "Buttons.h"
#include "Delay.h"
#include "Log.h"

void mediator_setup();
void mediator_loop();

void mediator_onDelayUp();
void mediator_onDelayDown();
void mediator_onDelayStep();
void mediator_onWaveNext();

#endif /* Mediator_H_ */
