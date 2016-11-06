#include "SetupRunner.h"
#include "WiFiCore.h"
#include "FileOrganizer.h"
#include "WebServer.h"
#include "Hardware.h"
#include "Global.h"
#include "Credentials.h"

void SetupWiFiEvent(WiFiEvent_t event) 
{
  switch(event) {
    case WIFI_EVENT_STAMODE_GOT_IP:
      char deviceIP[MAX_IP_LEN];
      char ssid[MAX_FILE_ATTR_LEN];
      char pass[MAX_FILE_ATTR_LEN];
      WiFiGetIP(deviceIP);
      Serial.printf("Trace   : WiFi connected. IP : %s\n", deviceIP);
      WiFiGetSSID(ssid);
      WiFiGetPassphrase(pass);
      FSStoreWiFiCredentials(ssid, pass);
      SETUPConfigStop();
      delay(1000);
      /* TaskRunner will help to run specific works to do on network connection. 
       * Until that time, reset the device. 
       * NOTE : Restarting will cause to lost connection before gathering succeed data on ESP-TOUCH SmartConfig.
      */
      HWRestart();
      break;
    case WIFI_EVENT_STAMODE_DISCONNECTED:
      Serial.printf("Warning : WiFi lost connection!\n");
      break;
  }
}

void startDummyConfig()
{
  WiFiBegin(STATION_DUMMY_SSID, STATION_DUMMY_PASS, SetupWiFiEvent);
}

void stopDummyConfig()
{
  WiFiStop();
}

boolean SETUPConfigCheck(char * ssid, char * pass)
{
  boolean retval = false;
  memset(ssid, 0, MAX_FILE_ATTR_LEN);
  memset(pass, 0, MAX_FILE_ATTR_LEN);
  
  if(FSCheckExistance(WIFI_CONFIG_FILE))
  {
    Serial.printf("Trace   : Config file found, connecting to Wifi.\n");
    char ssidRecord[MAX_FILE_ATTR_LEN];
    char passRecord[MAX_FILE_ATTR_LEN];
    
    if(FSReadConfig(WIFI_CONFIG_FILE, FILE_ATTR_SSID, ssidRecord))
    {
      /* Password may not exist. Test it! */
      FSReadConfig(WIFI_CONFIG_FILE, FILE_ATTR_PASSPHRASE, passRecord);
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
  
  return retval;
}

void SETUPConfigStart()
{
  FSDeleteFile(WIFI_CONFIG_FILE);
  /* Provide fn pointers for each mode and fill fn with related ops. */
#if defined(SETUP_DUMMY_CONFIG)
  startDummyConfig();
#elif defined(SETUP_SMART_CONFIG)
  WiFiStartSmart(SetupWiFiEvent);
#elif defined(SETUP_WEBSERVER_AP)
  WiFiSetAP(AP_SSID);
  WEBInit();
#endif
}

void SETUPConfigStop()
{
#if defined(SETUP_DUMMY_CONFIG)
  stopDummyConfig();
#elif  defined(SETUP_SMART_CONFIG)
  WiFiStopSmart();
#elif defined(SETUP_WEBSERVER_AP)
  WEBStop();
#endif
}

