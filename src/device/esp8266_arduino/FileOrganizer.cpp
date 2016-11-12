#include <ArduinoJson.h>

#include "FileOrganizer.h"
#include "FS.h"
#include "Global.h"

boolean FSInit()
{
  if (!SPIFFS.begin()) 
  {
    Serial.printf("Danger!!: Failed to mount file system!\n");
    return false;
  }
  return true;
}

boolean FSReadConfig(const char * filename, const char * parameter, char * returnValue)
{
  memset(returnValue, 0, MAX_FILE_ATTR_LEN);
  File configFileDesc = SPIFFS.open(filename, "r");
  if (!configFileDesc) 
  {
    Serial.printf("Error!  : FSReadConfig. Failed to open config file!\n");
    return false;
  }

  size_t size = configFileDesc.size();
  if (size > MAX_FILE_SIZE) 
  {
    Serial.printf("Error!  : FSReadConfig. Config file size is too large!\n");
    configFileDesc.close();
    return false;
  }

  char buf[size + 1];
  memset(buf, 0, size + 1);
  configFileDesc.readBytes(buf, size);

  StaticJsonBuffer<JSON_BUF_SIZE> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf);

  if (!json.success()) 
  {
    Serial.printf("Error!  : FSReadConfig. Failed to parse config file!\n");
    configFileDesc.close();
    return false;
  }

  const char* gathered = json[parameter];
  Serial.printf("Trace   : FSReadConfig. Read pair : %s -> %s\n", parameter, gathered);

  if(!gathered || !strlen(gathered))
  {
    Serial.printf("Error!  : FSReadConfig. Not a valid parameter value!\n");
    configFileDesc.close();
    return false;
  }

  strncpy(returnValue, json[parameter], strlen(json[parameter]));
  configFileDesc.close();
  Serial.printf("HEAP after read : %d\n",ESP.getFreeHeap());
  return true;
}

boolean FSWriteConfig(const char * filename, const char * parameter, const char * value)
{
  Serial.printf("HEAP FSWriteConfig begin : %d\n",ESP.getFreeHeap());
  File configFileDescReader = SPIFFS.open(filename, "a+");
  if (!configFileDescReader) 
  {
    Serial.printf("Error!  : Failed to open config file for writing\n");
    return false;
  }

  size_t size = configFileDescReader.size();
  if (size > MAX_FILE_SIZE) {
    Serial.printf("Error!  : FSWriteConfig. Config file size is too large!\n");
    configFileDescReader.close();
    return false;
  }
  else if (size == 0)
  {
    StaticJsonBuffer<JSON_BUF_SIZE / 2> jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    
    json[parameter] = value;
    
    Serial.printf("Trace   : FSWriteConfig. Written parameter is : %s\n", value);
    json.printTo(configFileDescReader);
  }
  else
  { 
    char buf[size + 1];
    memset(buf, 0, size + 1);
    configFileDescReader.readBytes(buf, size);
    configFileDescReader.close();
    StaticJsonBuffer<JSON_BUF_SIZE> jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(buf);
    if (!json.success()) 
    {
      Serial.printf("Error!  : FSWriteConfig. Failed to parse config file!! \n");
    }
    File configFileDescWriter = SPIFFS.open(filename, "w+");
    json[parameter] = value;

    Serial.printf("Trace   : FSWriteConfig. Gonna be written : %s\n", value);
    json.printTo(configFileDescWriter);
    configFileDescWriter.close();
  }
  configFileDescReader.close();
  Serial.printf("HEAP after write : %d\n",ESP.getFreeHeap());

  return true;
}

boolean FSCheckExistance(const char* filename)
{
  return SPIFFS.exists(filename);
}

void FSDeleteFile(const char* filename)
{
  SPIFFS.remove(filename);
}

boolean FSStoreWiFiCredentials(const char* ssid, const char* pass)
{
  boolean retval = false;

  Serial.printf("Trace   : FSStoreWiFiCredentials. SSID : %s\n", ssid);
  Serial.printf("Trace   : FSStoreWiFiCredentials PASS : %s\n", pass);

  FSDeleteFile(WIFI_CONFIG_FILE);
  
  if(ssid && strlen(ssid) && strlen(ssid) <= MAX_FILE_ATTR_LEN)
  {
    if(FSWriteConfig(WIFI_CONFIG_FILE, FILE_ATTR_SSID, ssid))
    {
      retval = true;
      if(pass && strlen(pass) && strlen(pass) <= MAX_FILE_ATTR_LEN)
      {
        Serial.println("Trace   : FSStoreWiFiCredentials. SSID written.");
        if(!FSWriteConfig(WIFI_CONFIG_FILE, FILE_ATTR_PASSPHRASE, pass))
        {
          retval = false;
          Serial.println("Error!  : FSStoreWiFiCredentials. Password cannot be written!");
        }
      }
      else
      {
        Serial.println("Warning: FSStoreWiFiCredentials. No Pass Network.");
      }
    }
    else
    {
      Serial.println("Danger!!: FSStoreWiFiCredentials. SSID cannot be written!!");
    }
  }
  else
  {
    Serial.println("Danger!!: FSStoreWiFiCredentials. SSID is not valid!!");
  }

  return retval;
}

