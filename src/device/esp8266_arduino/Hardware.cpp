#include <OneWire.h>

#include "Hardware.h"
#include "FileOrganizer.h"
#include "PinMap.h"
#include "TempSensor.h"
#include "Button.h"
#include "Global.h"

/* Library lacks empty constructor.
 * Not able to trigger from Hardware.cpp. Think to add it to the lib.
 */
OneWire oneWire(pinMap[2]);

void GPIOInit()
{
#ifdef USE_NODEMCU_BOARD
  pinMode(pinMap[0], OUTPUT);
  pinMode(pinMap[1], OUTPUT);
  
  HWSetGPIO(0, false);
  HWSetGPIO(1, false);
  /* pinMap[2] will be used for one-wire DQ. */
#elif defined(USE_DRAGON_BOARD)
  pinMode(pinMap[6], OUTPUT);
  pinMode(pinMap[7], OUTPUT);
#else
  pinMode(pinMap[6], OUTPUT);
  pinMode(pinMap[7], OUTPUT);
  /* pinMap[2] will be used for one-wire DQ. */
#endif

  delay(HW_DELAY);
}

void SerialInit()
{
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.setDebugOutput(true);
  delay(HW_DELAY);
}

void HWRestart()
{
  ESP.restart();
}

void HWSetGPIO(uint8_t pin, bool val)
{
  /* Implement GPIO map for different devices. */
#ifdef USE_LOW_LEVEL_TRIGGER
  digitalWrite(pinMap[pin], !val);
#else
  digitalWrite(pinMap[pin], val);
#endif
  delay(HW_DELAY);
}

bool HWGetGPIO(uint8_t pin)
{
#ifdef USE_LOW_LEVEL_TRIGGER
  return !digitalRead(pinMap[pin]);
#else
  /* Implement GPIO map for different devices. */
  return digitalRead(pinMap[pin]);
#endif
}

bool HWGetTempAsString(uint8_t id, char* tempBuf)
{
  return TEMPGetString(id, tempBuf);
}

void HWGetDeviceId(char *uid)
{
  /* Most device types use UUID. We may just use MAC or some concat. */
}

void HWInit()
{
  GPIOInit();
  SerialInit();
  FSInit();
  ButtonInit();
#ifdef USE_DS18B20_TEMP_SENSOR
  TEMPInit(&oneWire);
#endif
}

void HWLoop()
{
  ButtonLoop();
#ifdef USE_DS18B20_TEMP_SENSOR
  TEMPLoop();
#endif
}
