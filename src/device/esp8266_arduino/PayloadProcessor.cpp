#include <ArduinoJson.h>

#include "PayloadProcessor.h"
#include "WiFiCore.h"
#include "FileOrganizer.h"
#include "Hardware.h"
#include "Global.h"

boolean payloadDispatch(JsonObject& pObject)
{
  boolean retval = false;
  if (pObject[PAYLOAD_ATTR_ORIGIN].as<const char*>() && strcmp(pObject[PAYLOAD_ATTR_ORIGIN].as<const char*>(), PAYLOAD_ORIGIN_DEVICE) == 0)
  {
    Serial.printf("Warning: Payload will not be processed due to device origin.\n");
  }
  else
  {
    /* TODO: Use strncpy. */
    pObject[PAYLOAD_ATTR_ORIGIN] = PAYLOAD_ORIGIN_DEVICE;
    if(pObject[PAYLOAD_ATTR_TYPE].as<const char*>())
    {
      Serial.printf("Trace   : Payload attribute type : %s\n", pObject[PAYLOAD_ATTR_TYPE].as<const char*>());
      if (strcmp(pObject[PAYLOAD_ATTR_TYPE].as<const char*>(), PAYLOAD_DATA_AP_INFO) == 0)
      {
        retval = FSStoreWiFiCredentials(pObject[PAYLOAD_ATTR_SSID], pObject[PAYLOAD_ATTR_PASSPHRASE]);
      }
      else if (strcmp(pObject[PAYLOAD_ATTR_TYPE].as<const char*>(), PAYLOAD_DATA_AP_SEARCH) == 0)
      {
        /* Request visible WiFi networks from device. */
      }
      else if (strcmp(pObject[PAYLOAD_ATTR_TYPE].as<const char*>(), PAYLOAD_DATA_AP_DONE) == 0)
      {
        HWRestart();
        /* No need a return value due to restart. */
      }
      else if (strcmp(pObject[PAYLOAD_ATTR_TYPE].as<const char*>(), PAYLOAD_DATA_TIME_INFO) == 0)
      {
        /* If we gonna have NTP or RTC, this will make us to sync with user client. */
      }
      else if (strcmp(pObject[PAYLOAD_ATTR_TYPE].as<const char*>(), PAYLOAD_DATA_BRIDGE) == 0)
      {
        /* Functionize them all! */
        char deviceIP[MAX_IP_LEN];
        char ssid[MAX_FILE_ATTR_LEN];
        char pass[MAX_FILE_ATTR_LEN];
        WiFiGetIP(deviceIP);
        WiFiGetSSID(ssid);
        WiFiGetPassphrase(pass);
        pObject[PAYLOAD_ATTR_SSID] = ssid;
        pObject[PAYLOAD_ATTR_PASSPHRASE] = pass;
        pObject[PAYLOAD_ATTR_IP] = deviceIP;
        pObject[PAYLOAD_ATTR_SUCCESS] = 1;
        retval = true;
      }
      else if (strcmp(pObject[PAYLOAD_ATTR_TYPE], PAYLOAD_DATA_SWITCH) == 0)
      {
        /* Do Some GPIO operations */
      }
      else if (strcmp(pObject[PAYLOAD_ATTR_TYPE], PAYLOAD_DATA_TIMER) == 0)
      {
        /* Time triggered events. */
      }
      else if (strcmp(pObject[PAYLOAD_ATTR_TYPE], PAYLOAD_DATA_FACTORY) == 0)
      {
        FSDeleteFile(WIFI_CONFIG_FILE);
        HWRestart();
        /* No need a return value due to restart. */
      }
    }
  }

  return retval;
}

boolean payloadProcess(const char* payload, Protocol_t protocol)
{
 boolean retval = false;

 return retval;
}

boolean PAYLOADCompose(const char* type, const char* data, char* request)
{
  boolean retval = false;
  memset(request, 0, JSON_BUF_SIZE);
  StaticJsonBuffer<JSON_BUF_SIZE> jsonBuffer;
  JsonObject& deviceData = jsonBuffer.createObject();
  deviceData[PAYLOAD_ATTR_ORIGIN] = PAYLOAD_ORIGIN_DEVICE;
  /* Experimentally send deviceID as unique identifier. 
   * MAC would also be sent if non-ESP nodes included in the network.
   * Uniqe identifier will be needed to manage socket connection handles on cloud server side.
   */
  //deviceData[PAYLOAD_ATTR_DEVICE_ID] = ESP.getChipId();
  deviceData[PAYLOAD_ATTR_TYPE] = type;
  deviceData[PAYLOAD_ATTR_DATA] = data;
  deviceData[PAYLOAD_ATTR_SUCCESS] = 1;
  if(deviceData.printTo(request, JSON_BUF_SIZE))
  {
    retval = true;
  }
  else
  {
    Serial.printf("Error!  : Problem on coverting JSON to char array.\n");
  }

  return retval;
}

boolean PAYLOADParse(const char* payload, Protocol_t protocol, char* response)
{
  boolean retval = false;
  memset(response, 0, JSON_BUF_SIZE);
  if(strlen(payload))
  {
    StaticJsonBuffer<JSON_BUF_SIZE> jsonBuffer;
    JsonObject& payloadObject = jsonBuffer.parseObject(payload);
    if (payloadObject.success()) 
    {
      Serial.printf("Trace   : Payload has a valid JSON.\n");
      if(retval = payloadDispatch(payloadObject))
      {
        payloadObject.printTo(response, JSON_BUF_SIZE);
      }
    }
    else
    {
      Serial.printf("Warning: Processing raw data.\n");
      if(retval = payloadProcess(payload, protocol))
      {
        strncpy(response, payload, JSON_BUF_SIZE);
      }
    }
  }

  return retval;
}

