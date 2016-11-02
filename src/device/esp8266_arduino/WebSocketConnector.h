#ifndef ARDUINO_WEBSOCKETCONNECTOR_H
#define ARDUINO_WEBSOCKETCONNECTOR_H

#include <Arduino.h>

#define WS_TYPE_INIT  "ws_init"

void WSInit();
void WSLoop();
void WSDeliver(const char* type, const char* data);

#endif /* ARDUINO_WEBSOCKETCONNECTOR_H */
