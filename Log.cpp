#include "Log.h"

void log_setup() {
	Serial.begin(115200);
}

void ln(const char *fmt, ...) {
	char buf[80];

	Serial.print(">>");

	// print the message
	va_list va;
	va_start(va, fmt);
	vsprintf(buf, fmt, va);
	va_end(va);
	Serial.println(buf);
}

