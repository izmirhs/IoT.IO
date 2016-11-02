#include <ESP8266WiFi.h>

#include "SetupRunner.h"
#include "WiFiCore.h"
#include "FileOrganizer.h"
#include "Global.h"
#include "Credentials.h"

boolean storeWiFiCredentials()
{
  Serial.printf("Trace   : Storing WiFi Credentials ..\n");
  boolean retval = false;
  FSDeleteFile(WIFI_CONFIG_FILE);  
  char connectedSSID[MAX_FILE_ATTR_LEN];
  char connectedPass[MAX_FILE_ATTR_LEN];
  WiFi.SSID().toCharArray(connectedSSID, MAX_FILE_ATTR_LEN);
  WiFi.psk().toCharArray(connectedPass, MAX_FILE_ATTR_LEN);
  Serial.printf("Data    : SSID : %s\n",connectedSSID);
  Serial.printf("Data    : PASS : %s\n",connectedPass);
  if(FSWriteConfig(WIFI_CONFIG_FILE, ATTR_SSID, connectedSSID))
  {
    /* Need to test with no pass networks! */
    if(strlen(connectedPass))
    {
      FSWriteConfig(WIFI_CONFIG_FILE, ATTR_PASSPHRASE, connectedPass);
    }
    else
    {
      Serial.printf("Warning : No Password for WiFi ?\n");
    }
    Serial.printf("Trace   : WiFi Config is written.\n");
    retval = true;
  }
  else
  {
    Serial.printf("Danger!!: WiFi Config is CANNOT BE written!! \n");
  }

  return retval;
}

void SetupWiFiEvent(WiFiEvent_t event) 
{
  IPAddress myIP;
  switch(event) {
    case WIFI_EVENT_STAMODE_GOT_IP:
      myIP = WiFi.localIP();
      Serial.printf("Trace   : WiFi connected. IP : %d.%d.%d.%d\n", myIP[0],myIP[1],myIP[2],myIP[3]);
      storeWiFiCredentials();
      SETUPConfigStop();
      delay(1000);
      /* TaskRunner will help to run specific works to do on network connection. 
       * Until that time, reset the device. 
       * NOTE : Restarting will cause to lost connection before gathering succeed data on ESP-TOUCH SmartConfig.
      */
      ESP.restart();
      break;
    case WIFI_EVENT_STAMODE_DISCONNECTED:
      Serial.printf("Warning : WiFi lost connection!\n");
      break;
  }
}

void startSmartConfig()
{
  WiFiSetStation(SetupWiFiEvent);
  WiFi.beginSmartConfig();
  Serial.printf("Trace   : WiFi SmartConfig has begun.\n");
}

void stopSmartConfig()
{
  Serial.printf("Trace   : smartConfigDone -> %d\n",WiFi.smartConfigDone());
  if(WiFi.smartConfigDone())
  {
    WiFi.stopSmartConfig();
  }
}

void startDummyConfig()
{
  WiFiBegin(STATION_DUMMY_SSID, STATION_DUMMY_PASS, SetupWiFiEvent);
}

void stopDummyConfig()
{
  WiFi.disconnect();
}

boolean SETUPConfigCheck(char * ssid, char * pass)
{
  boolean retval = false;
  memset(ssid, 0, MAX_FILE_ATTR_LEN);
  memset(pass, 0, MAX_FILE_ATTR_LEN);
  if(FSInit())
  {
    if(FSCheckExistance(WIFI_CONFIG_FILE))
    {
      Serial.printf("Trace   : Config file found, connecting to Wifi.\n");
      char ssidRecord[MAX_FILE_ATTR_LEN];
      char passRecord[MAX_FILE_ATTR_LEN];
      /* Password may not exist. */
      if(FSReadConfig(WIFI_CONFIG_FILE, ATTR_SSID, ssidRecord))
      {
        FSReadConfig(WIFI_CONFIG_FILE, ATTR_PASSPHRASE, passRecord);
        Serial.printf("Data    : SSID Record: %s\n", ssidRecord);
        strncpy(ssid, ssidRecord, strlen(ssidRecord));
        strncpy(pass, passRecord, strlen(passRecord));
        retval = true;
      }
      else
      {
        Serial.printf("Error!  : SSID Read failed! Fallback to Setup Mode...\n");
      }
    }
    else
    {
      Serial.printf("Trace   : Config file NOT Found, Fallback to Setup Mode...\n");
    }
  }

  return retval;
}

void SETUPConfigStart()
{
  FSDeleteFile(WIFI_CONFIG_FILE);
  /* Provide fn pointers for each mode and fill fn with related ops. */
#ifdef SETUP_DUMMY_CONFIG
  startDummyConfig();
#elif defined(SETUP_SMART_CONFIG)
  startSmartConfig();
#endif
}

void SETUPConfigStop()
{
#ifdef SETUP_DUMMY_CONFIG
  stopDummyConfig();
#elif  defined(SETUP_SMART_CONFIG)
  stopSmartConfig();
#endif
}

