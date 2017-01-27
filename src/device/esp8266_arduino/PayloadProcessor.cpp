#include <ArduinoJson.h>

#include "PayloadProcessor.h"
#include "WiFiCore.h"
#include "FileOrganizer.h"
#include "Hardware.h"
#include "PinMap.h"
#include "TempSensor.h"
#include "Global.h"

bool payloadDispatch(JsonObject& pObject)
{
  bool retval = false;
  char type[PAYLOAD_ATTR_LEN] = {0};
  char origin[PAYLOAD_ATTR_LEN] = {0};
  
  if(pObject[PAYLOAD_ATTR_TYPE].as<const char*>())
  {
    strncpy(type, pObject[PAYLOAD_ATTR_TYPE].as<const char*>(), PAYLOAD_ATTR_LEN);
  }
  if(pObject[PAYLOAD_ATTR_ORIGIN].as<const char*>())
  {
    strncpy(origin, pObject[PAYLOAD_ATTR_ORIGIN].as<const char*>(), PAYLOAD_ATTR_LEN);
  }
  if (origin && strcmp(origin, PAYLOAD_ORIGIN_DEVICE) == 0)
  {
    Serial.printf("Warning: Payload will not be processed due to device origin.\n");
  }
  else
  {
    /* JSON attribute is a class type and has operator overloading for equation. */
    pObject[PAYLOAD_ATTR_ORIGIN] = PAYLOAD_ORIGIN_DEVICE;
    if(type)
    {
      Serial.printf("Trace   : Payload attribute type : %s\n", type);
      
      if (strcmp(type, PAYLOAD_DATA_AP_INFO) == 0)
      {
        if(pObject[PAYLOAD_ATTR_SSID].as<const char*>())
        {
          retval = FSStoreWiFiCredentials(pObject[PAYLOAD_ATTR_SSID], pObject[PAYLOAD_ATTR_PASSPHRASE]);
          pObject[PAYLOAD_ATTR_DEVICE_ID] = ESP.getChipId();
        }
        else
        {
          Serial.printf("Error!  : Payload has no valid SSID data.\n");
        }
      }
      else if (strcmp(type, PAYLOAD_DATA_AP_SEARCH) == 0)
      {
        /* Request visible WiFi networks from device. */
      }
      else if (strcmp(type, PAYLOAD_DATA_AP_POLL) == 0)
      {
        /* Just succeed it, no data to transmit. */
        retval = true;
      }
      else if (strcmp(type, PAYLOAD_DATA_AP_DONE) == 0)
      {
        HWRestart();
        /* No need a return value due to restart. */
      }
      else if (strcmp(type, PAYLOAD_DATA_TIME_INFO) == 0)
      {
        /* If we gonna have NTP or RTC, this will make us to sync with user client. */
      }
      else if (strcmp(type, PAYLOAD_DATA_BRIDGE) == 0)
      {
        /* Functionize them all! */
        char deviceIP[MAX_IP_LEN];
        char ssid[MAX_FILE_ATTR_LEN];
        char pass[MAX_FILE_ATTR_LEN];
        WiFiGetIP(deviceIP);
        pObject[PAYLOAD_ATTR_IP] = deviceIP;
        WiFiGetSSID(ssid);
        pObject[PAYLOAD_ATTR_SSID] = ssid;
        WiFiGetPassphrase(pass);
        pObject[PAYLOAD_ATTR_PASSPHRASE] = pass;
        retval = true;
      }
      else if (strcmp(type, PAYLOAD_DATA_STATUS) == 0)
      {
        JsonArray& pinStats = pObject.createNestedArray("pins");
        /* Perform a loop for max pin count. */
        pinStats.add((uint8_t)HWGetGPIO(0));
        pinStats.add((uint8_t)HWGetGPIO(1));
        char tempBuffer[LEN_TEMP_MAX];
        if(TEMPGetString(0, tempBuffer))
        {
          JsonArray& sensorStats = pObject.createNestedArray("sensors");
          sensorStats.add(tempBuffer);
        }
        retval = true;
      }
      else if (strcmp(type, PAYLOAD_DATA_SWITCH) == 0)
      {
        unsigned short switchNo = pObject[PAYLOAD_ATTR_ID].as<unsigned short>();
        /* Pin numbers are starting from 1 from user side. */
        if(switchNo > 0 && switchNo <= MAX_PIN_CNT)
        {
          unsigned short pinOnDevice = switchNo - 1;
          HWSetGPIO(pinOnDevice, !HWGetGPIO(pinOnDevice));
          pObject[PAYLOAD_ATTR_DATA] = (uint8_t)HWGetGPIO(pinOnDevice);
          retval = true;
        }
      }
      else if (strcmp(type, PAYLOAD_DATA_TIMER) == 0)
      {
        /* Time triggered events. */
      }
      else if (strcmp(type, PAYLOAD_DATA_FACTORY) == 0)
      {
        FSDeleteFile(WIFI_CONFIG_FILE);
        HWRestart();
        /* No need a return value due to restart. */
      }
    }
  }

  return retval;
}

bool payloadProcess(const char* payload, Protocol_t protocol)
{
  bool retval = false;

  return retval;
}

bool PAYLOADCompose(const char* type, const char* data, char* request)
{
  bool retval = false;
  memset(request, 0, JSON_BUF_SIZE);
  StaticJsonBuffer<JSON_BUF_SIZE> jsonBuffer;
  JsonObject& deviceData = jsonBuffer.createObject();
  deviceData[PAYLOAD_ATTR_ORIGIN] = PAYLOAD_ORIGIN_DEVICE;
  /* Experimentally send deviceID as unique identifier. 
   * MAC would also be sent if non-ESP nodes included in the network.
   * Uniqe identifier will be needed to manage socket connection handles on cloud server side.
   */
  deviceData[PAYLOAD_ATTR_DEVICE_ID] = ESP.getChipId();
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

bool PAYLOADParse(const char* payload, Protocol_t protocol, char* response)
{
  bool retval = false;
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
        payloadObject[PAYLOAD_ATTR_SUCCESS] = 1;
        payloadObject.printTo(response, JSON_BUF_SIZE);
      }
      else
      {
        /* Payload with no success will not be processed on userclient. */
        Serial.printf("Error!  : Dispatch failed!\n");
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

