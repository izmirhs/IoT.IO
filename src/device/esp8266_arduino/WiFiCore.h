#ifndef ARDUINO_WIFICORE_H
#define ARDUINO_WIFICORE_H

#include <ESP8266WiFi.h>

static const IPAddress APAddr(192, 168, 99, 1); 
static const IPAddress APMask(255, 255, 255, 0);

void WiFiSetStation(WiFiEventCb fn);
void WiFiSetAP(const char* accessPointName);
void WiFiBegin(const char* ssid, const char* pass, WiFiEventCb wifiEventCb);
void WiFiStop();
void WiFiStartSmart(WiFiEventCb wifiEventCb);
void WiFiStopSmart();
void WiFiGetIP(char* ipBuffer);
void WiFiGetSSID(char* ssidBuffer);
void WiFiGetPassphrase(char* passBuffer);

#endif /* ARDUINO_WIFICORE_H */
