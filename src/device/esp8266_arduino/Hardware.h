#ifndef ARDUINO_HARDWARE_H
#define ARDUINO_HARDWARE_H

#include <Arduino.h>
#include <OneWire.h>

void HWInit();
void HWRestart();
void HWGetUniqeId(char *uid);
void HWLoop();
OneWire* getWire();

#endif /* ARDUINO_HARDWARE_H */
