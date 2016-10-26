#ifndef ARDUINO_FILECONTROLLER_H
#define ARDUINO_FILECONTROLLER_H

#include <Arduino.h>

#define WIFI_CONFIG_FILE    "/config.json"
#define TIMERS_CONFIG_FILE  "/timers.json"

#define ATTR_SSID           "SSID"
#define ATTR_PASSPHRASE     "PASS"

boolean FSInit();
boolean FSWriteConfig(const char * filename, const char * parameter, const char * value);
boolean FSReadConfig(const char * filename, const char * parameter, char * returnValue);
boolean FSCheckExistance(const char* filename);
void FSDeleteFile(const char* filename);

#endif /* ARDUINO_FILECONTROLLER_H */
