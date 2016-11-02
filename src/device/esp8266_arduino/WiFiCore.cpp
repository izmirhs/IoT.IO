#include "WiFiCore.h"
#include "Global.h"

void WiFiSetStation(WiFiEventCb wifiEventCb)
{
  WiFi.softAPdisconnect();
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  delay(500);
  WiFi.onEvent(wifiEventCb);
}

void WiFiSetAP(const char* accessPointName)
{
  Serial.printf("Trace   : Configuring access point ..\n");
  WiFi.disconnect();
  WiFi.softAPdisconnect();
  delay(10);
  IPAddress APAddr(192, 168, 99, 1); 
  IPAddress APMask(255, 255, 255, 0);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(APAddr, APAddr, APMask);
  WiFi.softAP(accessPointName);
  delay(10);
  IPAddress myIP = WiFi.softAPIP();
  Serial.printf("Trace   : AP IP address: %d.%d.%d.%d\n", myIP[0],myIP[1],myIP[2],myIP[3]);
}

void WiFiBegin(const char* ssid, const char* pass, WiFiEventCb wifiEventCb)
{
  WiFiSetStation(wifiEventCb);
  if(strlen(ssid) && strlen(pass))
  {
    WiFi.begin(ssid, pass);
  }
  else
  {
    WiFi.begin(ssid);
  }
  Serial.printf("Trace   : WiFi has begun.\n");
}

void WiFiStop()
{
  WiFi.softAPdisconnect();
  WiFi.disconnect();
}

void WiFiStartSmart(WiFiEventCb wifiEventCb)
{
  WiFiSetStation(wifiEventCb);
  WiFi.beginSmartConfig();
  Serial.printf("Trace   : WiFi SmartConfig has begun.\n");
}

void WiFiStopSmart()
{
  Serial.printf("Trace   : smartConfigDone -> %d\n",WiFi.smartConfigDone());
  if(WiFi.smartConfigDone())
  {
    WiFi.stopSmartConfig();
  }
}

