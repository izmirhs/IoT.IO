#ifndef ARDUINO_PAYLOADPROCESSOR_H
#define ARDUINO_PAYLOADPROCESSOR_H

#include <Arduino.h>
#include "PayloadTypes.h"
#include "Global.h"

bool PAYLOADCompose(const char* type, const char* data, char* request);
bool PAYLOADParse(const char* payload, Protocol_t protocol, char* response);

#endif /* ARDUINO_PAYLOADPROCESSOR_H */
