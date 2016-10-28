#ifndef ARDUINO_WEBSOCKETCONNECTOR_H
#define ARDUINO_WEBSOCKETCONNECTOR_H

#include <Arduino.h>

void WSInit();
void WSLoop();
void WSDeliver(const char* type, const char* data);

#endif /* ARDUINO_WEBSOCKETCONNECTOR_H */
