#ifndef ARDUINO_WIFICORE_H
#define ARDUINO_WIFICORE_H

#include <ESP8266WiFi.h>

void WiFiSetStation(WiFiEventCb fn);
void WiFiSetAP();
void WiFiBegin(const char* ssid, const char* pass, WiFiEventCb wifiEventCb);

#endif /* ARDUINO_WIFICORE_H */
