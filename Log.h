#ifndef Log_H_
#define Log_H_

#include "Arduino.h"
#include "stdarg.h"

void log_setup();
void ln(const char *fmt, ...);

#endif /* Log_H_ */
