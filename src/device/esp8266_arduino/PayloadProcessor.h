#ifndef ARDUINO_PAYLOADPROCESSOR_H
#define ARDUINO_PAYLOADPROCESSOR_H

#include <Arduino.h>

#define PAYLOAD_DATA_AP_INFO    "APInfo"
#define PAYLOAD_DATA_AP_SEARCH  "APSearch"
#define PAYLOAD_DATA_AP_DONE    "APDone"
#define PAYLOAD_DATA_TIME_INFO  "TimeInfo"

#define PAYLOAD_ATTR_TYPE       "type"
#define PAYLOAD_ATTR_DATA       "data"
#define PAYLOAD_ATTR_SUCCESS    "success"
#define PAYLOAD_ATTR_SSID       "ssid"
#define PAYLOAD_ATTR_PASSPHRASE "pass"
#define PAYLOAD_ATTR_ORIGIN     "origin"

String PAYLOADCompose(const char* type, const char* data);
boolean PAYLOADParse(const char* payload);

#endif /* ARDUINO_PAYLOADPROCESSOR_H */
