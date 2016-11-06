#include "NetworkAdapter.h"
#include "SetupRunner.h"
#include "WiFiCore.h"
#include "WebSocketConnector.h"
#include "MQTTConnector.h"
#include "WebServer.h"
#include "Global.h"

void NETEvent(WiFiEvent_t event) 
{
  switch(event) {
    case WIFI_EVENT_STAMODE_GOT_IP:
#ifdef PROTOCOL_WEBSOCKET
      WSOCKInit();
#elif defined(PROTOCOL_MQTT)
      MQTTInit();
#endif
      char deviceIP[MAX_IP_LEN];
      WiFiGetIP(deviceIP);
      Serial.printf("Trace   : WiFi connected. IP : %s\n", deviceIP);
      break;
    case WIFI_EVENT_STAMODE_DISCONNECTED:
      Serial.printf("Warning : WiFi lost connection!\n");
      break;
  }
}

void NETBegin()
{
  char ssidGathered[MAX_FILE_ATTR_LEN];
  char passGathered[MAX_FILE_ATTR_LEN];
  if(SETUPConfigCheck(ssidGathered, passGathered))
  {
    WiFiBegin(ssidGathered, passGathered, NETEvent);
  }
  else
  {
    SETUPConfigStart();
  }
}

void NETLoop()
{
  WSOCKLoop();
  MQTTLoop();
  WEBLoop();
}


