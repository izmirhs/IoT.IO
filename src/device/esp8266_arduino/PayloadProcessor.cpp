#include <ArduinoJson.h>

#include "PayloadProcessor.h"
#include "Global.h"

String PAYLOADCompose(const char* type, const char* data)
{
  StaticJsonBuffer<JSON_BUF_SIZE> jsonBuffer;
  JsonObject& deviceData = jsonBuffer.createObject();
  String jsonToSend;
  deviceData["origin"] = "device";
  /* Experimentally send deviceID as unique identifier. 
   * MAC would also be sent if non-ESP nodes included in the network.
   * Uniqe identifier will be needed to manage socket connection handles on cloud server side.
   */
  //deviceData["deviceId"] = ESP.getChipId();
  deviceData["type"] = type;
  deviceData["data"] = data;
  deviceData["succeed"] = 1;
  deviceData.printTo(jsonToSend);

  return jsonToSend;
}

boolean PAYLOADParse(const char* payload)
{
  boolean retval = false;
  if(strlen(payload))
  {
    StaticJsonBuffer<JSON_BUF_SIZE> jsonBuffer;
    JsonObject& data = jsonBuffer.parseObject(payload);
    if (!data.success()) 
    {
      /* JSON type may not be used on future, so re-shape the parsing method. */
      Serial.printf("Error!  : Not a valid JSON string gathered !!!\n");
    }
    else
    {
      retval = true;
      Serial.printf("Trace   : Payload parsing succeeded.\n");
      if(data["type"].as<const char*>() && data["data"].as<const char*>())
      {
        Serial.printf("Trace   : Parsed payload type : %s\n", data["type"].as<const char*>());
        Serial.printf("Trace   : Parsed payload data : %s\n", data["data"].as<const char*>());
      }
      else
      {
        Serial.printf("Warning: Payload has no specifid fields.\n");
      }
      
      /* Do your operation in here regarding to gathered data !*/
      
    }
  }

  return retval;
}

