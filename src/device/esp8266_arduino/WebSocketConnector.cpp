#include <WebSocketsClient.h>

#include "WebSocketConnector.h"
#include "Global.h"
#include "Credentials.h"

#include <ArduinoJson.h>

WebSocketsClient wsClient;
boolean ws_init_done = false;

String PROCWebSocketDelivery(const char* type, const char* data)
{
  StaticJsonBuffer<JSON_BUF_SIZE> jsonBuffer;
  JsonObject& deviceData = jsonBuffer.createObject();
  String jsonToSend;
  deviceData["origin"] = "device";
  deviceData["deviceId"] = ESP.getChipId();
  deviceData["type"] = type;
  deviceData["data"] = data;
  deviceData["succeed"] = 1;
  deviceData.printTo(jsonToSend);

  return jsonToSend;
}

void WSDeliver(const char* type, const char* data)
{
  String delivery = PROCWebSocketDelivery(type, data);
  wsClient.sendTXT(delivery);
}

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
        char deviceId[MAX_JSON_ATTR_LEN];
        String(ESP.getChipId()).toCharArray(deviceId, MAX_JSON_ATTR_LEN);
        WSDeliver("ws_init", deviceId);
      }
      break;
    case WStype_TEXT:
      Serial.printf("Data    : webSocketEvent. Text gathered : %s\n", payload);

      /* Process incoming WebSocket data in here. */
      
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
  //wsClient.setAuthorization("user", "Password");
  wsClient.onEvent(webSocketEvent);
  ws_init_done = true;
}

WebSocketsClient WSClient()
{
  return wsClient;
}

void WSLoop()
{
  wsClient.loop();
}

