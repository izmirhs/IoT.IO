#ifndef ARDUINO_HARDWARE_H
#define ARDUINO_HARDWARE_H

#include <Arduino.h>

/* Definitions for constants.  */
#define HW_DELAY 10

/* Definitions for external devices. */
#define USE_DS18B20_TEMP_SENSOR
#define USE_LOW_LEVEL_TRIGGER

void HWInit();
void HWRestart();
void HWGetUniqeId(char *uid);
void HWSetGPIO(uint8_t pin, bool val);
bool HWGetGPIO(uint8_t pin);
void HWLoop();

#endif /* ARDUINO_HARDWARE_H */
