#ifndef ARDUINO_PINMAP_H
#define ARDUINO_PINMAP_H

#include <Arduino.h>

#define MAX_PIN_CNT 11

/* GPIO Definitions */
static const uint8_t pinMap[MAX_PIN_CNT]            = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1};
static const uint8_t pinMapCustom[MAX_PIN_CNT]      = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1};
static const uint8_t pinMapDragonBoard[MAX_PIN_CNT] = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1};

#endif /* ARDUINO_PINMAP_H */
