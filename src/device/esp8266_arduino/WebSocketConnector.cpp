#include <WebSocketsClient.h>

#include "WebSocketConnector.h"
#include "PayloadProcessor.h"
#include "Global.h"
#include "Credentials.h"

WebSocketsClient wsClient;
boolean ws_init_done = false;

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
        WSDeliver(WS_TYPE_INIT, String(ESP.getChipId()).c_str());
      }
      break;
    case WStype_TEXT:
      Serial.printf("Data    : webSocketEvent. Text gathered : %s\n", payload);

      PAYLOADParse((const char*)payload);
      
      break;
    case WStype_BIN:
      Serial.printf("Data    : webSocketEvent. Data gathered : %u\n", lenght);
      hexdump(payload, lenght);
      break;
  }
}

void WSInit()
{
  /* Path gonna be used. */
  wsClient.begin(WS_HOST, WS_PORT /*, String(ESP.getChipId())*/);
  /* Some authorization and SSL must be performed. */
  //wsClient.setAuthorization("user", "Password");
  wsClient.onEvent(webSocketEvent);
  ws_init_done = true;
}

void WSDeliver(const char* type, const char* data)
{
  String payload = PAYLOADCompose(type, data);
  wsClient.sendTXT(payload);
}

WebSocketsClient WSClient()
{
  return wsClient;
}

void WSLoop()
{
  if(ws_init_done)
  {
    wsClient.loop();
  }
}

