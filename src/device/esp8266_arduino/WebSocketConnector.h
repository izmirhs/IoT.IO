#ifndef ARDUINO_WEBSOCKETCONNECTOR_H
#define ARDUINO_WEBSOCKETCONNECTOR_H

#include <Arduino.h>

void WSOCKInit();
void WSOCKLoop();
bool WSOCKDeliver(const char* type, const char* data);

#endif /* ARDUINO_WEBSOCKETCONNECTOR_H */
