#include <DallasTemperature.h>

#include "TempSensor.h"
#include "Hardware.h"
#include "Global.h"

DallasTemperature sense18B20;
DeviceAddress thermos;

void printAddress(DeviceAddress deviceAddress)
{
  Printf("Data    : printAddress. Sensor Address :\n");
  const uint8_t addr_len = 8;
  for (uint8_t i = 0; i < addr_len; i++)
  {
    Printf("%x", deviceAddress[i]);
  }
  Printf("\n");
}

void printTemperature()
{
  char tempStr[LEN_TEMP_MAX];
  TEMPGetString(0, tempStr);
  if(strlen(tempStr))
  {
    Printf("Data    : printTemperature. %s\n", tempStr);
  }
  else
  {
    Printf("Error!  : Could not retrieve sensor data!\n");
  }
}

void TEMPInit(OneWire* oneWire)
{
  sense18B20.setOneWire(oneWire);
  sense18B20.begin();
  Printf("Trace   : Found %d Sensor devices.\n", sense18B20.getDeviceCount());
}

float TEMPGet(uint8_t id)
{
  float retval = INVALID_TEMP_READ;
  DeviceAddress temper;
  if (sense18B20.getDeviceCount() && sense18B20.getAddress(temper, id))
  {
    sense18B20.setResolution(temper, SENSOR_SENSITIVITY);
    retval = sense18B20.getTempC(temper);
  }

  return retval;
}

void TEMPGetString(uint8_t id, char* tempBuffer)
{
    float sensorData = TEMPGet(id);
    const uint8_t data_len = 3;
    const uint8_t data_prec_len = 2;
    dtostrf(sensorData, data_len, data_prec_len, tempBuffer);
}

void TEMPLoop()
{
  if(sense18B20.getDeviceCount())
  {
    sense18B20.requestTemperatures();
  }
}


