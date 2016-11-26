#ifndef ARDUINO_TEMPSENSOR_H
#define ARDUINO_TEMPSENSOR_H

#include <Arduino.h>
#include <OneWire.h>

#define INVALID_TEMP_READ   -196
#define SENSOR_SENSITIVITY  12

void  TEMPInit(OneWire* wire);
float TEMPGet(uint8_t id);
void  TEMPGetString(uint8_t id, char* tempBuffer);
void  TEMPLoop();

#endif /* ARDUINO_TEMPSENSOR_H */
