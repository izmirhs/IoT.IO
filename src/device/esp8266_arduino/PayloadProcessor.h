#ifndef ARDUINO_PAYLOADPROCESSOR_H
#define ARDUINO_PAYLOADPROCESSOR_H

#include <Arduino.h>

String PAYLOADCompose(const char* type, const char* data);
boolean PAYLOADParse(const char* payload);

#endif /* ARDUINO_PAYLOADPROCESSOR_H */
