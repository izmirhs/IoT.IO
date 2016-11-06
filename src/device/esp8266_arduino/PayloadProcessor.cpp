#include <ArduinoJson.h>

#include "PayloadProcessor.h"
#include "FileOrganizer.h"
#include "Hardware.h"
#include "Global.h"

boolean payloadDispatcher(JsonObject& pObject)
{
  boolean retval = false;
  Serial.printf("Trace   : Payload received : %s\n", pObject[PAYLOAD_ATTR_TYPE]);
  
  if (strcmp(pObject[PAYLOAD_ATTR_TYPE], PAYLOAD_DATA_AP_INFO) == 0)
  {
    retval = FSStoreWiFiCredentials(pObject[PAYLOAD_ATTR_SSID], pObject[PAYLOAD_ATTR_PASSPHRASE]);
  }
  else if (strcmp(pObject[PAYLOAD_ATTR_TYPE], PAYLOAD_DATA_AP_SEARCH) == 0)
  {
    /* Request visible WiFi networks from device. */
  }
  else if (strcmp(pObject[PAYLOAD_ATTR_TYPE], PAYLOAD_DATA_AP_DONE) == 0)
  {
    HWRestart();
  }
  else if (strcmp(pObject[PAYLOAD_ATTR_TYPE], PAYLOAD_DATA_TIME_INFO) == 0)
  {
    /* If we gonna have NTP or RTC, this will make us to sync with user client. */
  }

  return retval;
}

/* Returning a String? Cmon. */
String PAYLOADCompose(const char* type, const char* data)
{
  StaticJsonBuffer<JSON_BUF_SIZE> jsonBuffer;
  JsonObject& deviceData = jsonBuffer.createObject();
  String jsonToSend;
  deviceData[PAYLOAD_ATTR_ORIGIN] = "device";
  /* Experimentally send deviceID as unique identifier. 
   * MAC would also be sent if non-ESP nodes included in the network.
   * Uniqe identifier will be needed to manage socket connection handles on cloud server side.
   */
  //deviceData["deviceId"] = ESP.getChipId();
  deviceData[PAYLOAD_ATTR_TYPE] = type;
  deviceData[PAYLOAD_ATTR_DATA] = data;
  deviceData[PAYLOAD_ATTR_SUCCESS] = 1;
  deviceData.printTo(jsonToSend);

  return jsonToSend;
}

boolean PAYLOADParse(const char* payload)
{
  boolean retval = false;
  if(strlen(payload))
  {
    StaticJsonBuffer<JSON_BUF_SIZE> jsonBuffer;
    JsonObject& payloadObject = jsonBuffer.parseObject(payload);
    if (!payloadObject.success()) 
    {
      /* JSON type may not be used on future, so re-shape the parsing method. */
      Serial.printf("Error!  : Not a valid JSON string gathered !!!\n");
    }
    else
    {
      Serial.printf("Trace   : Payload parsing succeeded.\n");
      retval = payloadDispatcher(payloadObject);
    }
  }

  return retval;
}

