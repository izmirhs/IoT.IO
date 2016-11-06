#include "WiFiCore.h"
#include "Global.h"

const uint8_t wifiDeviceDelay = 50;

void WiFiSetStation(WiFiEventCb wifiEventCb)
{
  WiFi.softAPdisconnect();
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  delay(wifiDeviceDelay);
  WiFi.onEvent(wifiEventCb);
}

void WiFiSetAP(const char* accessPointName)
{
  Serial.printf("Trace   : Configuring access point ..\n");
  WiFi.disconnect();
  WiFi.softAPdisconnect();
  delay(wifiDeviceDelay);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(APAddr, APAddr, APMask);
  WiFi.softAP(accessPointName);
  delay(wifiDeviceDelay);
  IPAddress myIP = WiFi.softAPIP();
  Serial.printf("Trace   : AP IP address: %d.%d.%d.%d\n", myIP[0],myIP[1],myIP[2],myIP[3]);
}

void WiFiBegin(const char* ssid, const char* pass, WiFiEventCb wifiEventCb)
{
  /* Pass reference in here! */
  if(wifiEventCb)
  {
    WiFiSetStation(wifiEventCb);
  }
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

void WiFiGetIP(char* ipBuffer)
{
  memset(ipBuffer, 0, MAX_IP_LEN);
  IPAddress ip = WiFi.localIP();
  snprintf(ipBuffer, MAX_IP_LEN, "%d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);
}

void WiFiGetSSID(char* ssidBuffer)
{
  memset(ssidBuffer, 0, MAX_FILE_ATTR_LEN);
  strncpy(ssidBuffer, WiFi.SSID().c_str(), MAX_FILE_ATTR_LEN);
}

void WiFiGetPassphrase(char* passBuffer)
{
  memset(passBuffer, 0, MAX_FILE_ATTR_LEN);
  strncpy(passBuffer, WiFi.psk().c_str(), MAX_FILE_ATTR_LEN);
}


