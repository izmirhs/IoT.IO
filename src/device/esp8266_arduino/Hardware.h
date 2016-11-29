#ifndef ARDUINO_HARDWARE_H
#define ARDUINO_HARDWARE_H

#include <Arduino.h>

/* Definitions for constants.  */
#define MAX_PIN_CNT     11
#define BUTTON_ACT_SEC  3
/* Definitions for external devices.  */
#define USE_DS18B20_TEMP_SENSOR

void HWInit();
void HWRestart();
void HWGetUniqeId(char *uid);
void HWSetGPIO(uint8_t pin, bool val);
bool HWGetGPIO(uint8_t pin);
void HWLoop();

/* GPIO Definitions */
static const uint8_t pinMap[MAX_PIN_CNT] = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1};
static const uint8_t pinMapCustom[MAX_PIN_CNT] = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1};
static const uint8_t pinMapDragonBoard[MAX_PIN_CNT] = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1};

#endif /* ARDUINO_HARDWARE_H */
