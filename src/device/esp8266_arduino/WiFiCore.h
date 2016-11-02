#ifndef ARDUINO_WIFICORE_H
#define ARDUINO_WIFICORE_H

#include <ESP8266WiFi.h>

void WiFiSetStation(WiFiEventCb fn);
void WiFiSetAP(const char* accessPointName);
void WiFiBegin(const char* ssid, const char* pass, WiFiEventCb wifiEventCb);
void WiFiStop();
void WiFiStartSmart(WiFiEventCb wifiEventCb);
void WiFiStopSmart();

#endif /* ARDUINO_WIFICORE_H */
