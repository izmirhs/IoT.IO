#ifndef ARDUINO_FILEORGANIZER_H
#define ARDUINO_FILEORGANIZER_H

#include <Arduino.h>

#define WIFI_CONFIG_FILE      "/config.json"
#define WSOCK_CONFIG_FILE     "/wsock.json"
#define TIMERS_CONFIG_FILE    "/timers.json"

#define FILE_ATTR_SSID        "ssid"
#define FILE_ATTR_PASSPHRASE  "pass"
#define FILE_ATTR_USER        "user"

boolean FSInit();
boolean FSWriteConfig(const char * filename, const char * parameter, const char * value);
boolean FSReadConfig(const char * filename, const char * parameter, char * returnValue);
boolean FSCheckExistance(const char* filename);
void    FSDeleteFile(const char* filename);
boolean FSStoreWiFiCredentials(const char* ssid, const char* pass);

#endif /* ARDUINO_FILEORGANIZER_H */
