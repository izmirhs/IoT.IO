#ifndef ARDUINO_PAYLOADPROCESSOR_H
#define ARDUINO_PAYLOADPROCESSOR_H

#include <Arduino.h>
#include "Global.h"

/* Setup Payload Data */
#define PAYLOAD_DATA_AP_INFO    "APInfo"
#define PAYLOAD_DATA_AP_SEARCH  "APSearch"
#define PAYLOAD_DATA_AP_DONE    "APDone"
#define PAYLOAD_DATA_TIME_INFO  "TimeInfo"
/* Runtime Payload Data */
#define PAYLOAD_DATA_LEN        64
#define PAYLOAD_DATA_BRIDGE     "Bridge"
#define PAYLOAD_DATA_SWITCH     "Switch"
#define PAYLOAD_DATA_TIMER      "Timer"
#define PAYLOAD_DATA_FACTORY    "Factory"
/* Attribure name identifiers delivered with Payload */
#define PAYLOAD_ATTR_LEN        16
#define PAYLOAD_ATTR_TYPE       "type"
#define PAYLOAD_ATTR_DATA       "data"
#define PAYLOAD_ATTR_SUCCESS    "succeed"
#define PAYLOAD_ATTR_SSID       "ssid"
#define PAYLOAD_ATTR_PASSPHRASE "pass"
#define PAYLOAD_ATTR_IP         "ip"
#define PAYLOAD_ATTR_DEVICE_ID  "deviceId"
#define PAYLOAD_ATTR_ORIGIN     "origin"

#define PAYLOAD_ORIGIN_DEVICE   "device"

boolean PAYLOADCompose(const char* type, const char* data, char* request);
boolean PAYLOADParse(const char* payload, Protocol_t protocol, char* response);

#endif /* ARDUINO_PAYLOADPROCESSOR_H */
