#include <WebSocketsClient.h>

#include "WebSocketConnector.h"
#include "PayloadProcessor.h"
#include "Global.h"
#include "Credentials.h"

WebSocketsClient wsClient;
static const Protocol_t protocol = WebSocket;
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
      char response[JSON_BUF_SIZE];
      PAYLOADParse((const char*)payload, protocol, response);
      if(response && strlen(response))
      {
        /* Send back incoming text with filling requested data.
         * As SebSocket is an async protocol, we may put requests in a queue to process.
         * So we gonna need to put an identifier to all incoming data and store in structs.
         */
        wsClient.sendTXT(response);
      }
      else
      {
        Serial.printf("Error!  : webSocketEvent. Request connot be processed correctly !!!\n");
      }
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
  char request[JSON_BUF_SIZE];
  if(PAYLOADCompose(type, data, request))
  {
    wsClient.sendTXT(request);
  }
}

void WSOCKLoop()
{
  if(wsInitCompleted)
  {
    wsClient.loop();
  }
}

