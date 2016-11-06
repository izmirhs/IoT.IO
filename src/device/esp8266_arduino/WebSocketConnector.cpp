#include <WebSocketsClient.h>

#include "WebSocketConnector.h"
#include "PayloadProcessor.h"
#include "Global.h"
#include "Credentials.h"

WebSocketsClient wsClient;
boolean wsInitCompleted = false;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) 
{
  String response = "";
  switch (type) { 
    case WStype_DISCONNECTED:
      {
        wsClient.disconnect();
        Serial.printf("Error!  : webSocketEvent. Disconnected!\n");
      }
      break;
    case WStype_CONNECTED:
      {
        Serial.printf("Trace   : webSocketEvent. Connected to url: %s\n",  payload);
        WSOCKDeliver(WS_TYPE_INIT, String(ESP.getChipId()).c_str());
      }
      break;
    case WStype_TEXT:
      Serial.printf("Data    : webSocketEvent. Text gathered : %s\n", payload);

      /* Process incoming WebSocket data in here. */
      PAYLOADParse((const char*)payload);
      
      break;
    case WStype_BIN:
      Serial.printf("Data    : webSocketEvent. Data gathered : %u\n", lenght);
      hexdump(payload, lenght);
      break;
  }
}

void WSOCKInit()
{
  /* Path gonna be used. */
  wsClient.begin(WSOCK_HOST, WSOCK_PORT /*, String(ESP.getChipId())*/);
  /* Some authorization and SSL must be performed. */
  //wsClient.setAuthorization("user", "Password");
  wsClient.onEvent(webSocketEvent);
  wsInitCompleted = true;
}

void WSOCKDeliver(const char* type, const char* data)
{
  String payload = PAYLOADCompose(type, data);
  wsClient.sendTXT(payload);
}

void WSOCKLoop()
{
  if(wsInitCompleted)
  {
    wsClient.loop();
  }
}

