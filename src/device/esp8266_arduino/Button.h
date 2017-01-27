#ifndef ARDUINO_BUTTON_H
#define ARDUINO_BUTTON_H

#include <Arduino.h>

/* Button activation in seconds. */
#define BUTTON_ACTIVATION_SECS  3

void ButtonInit();
void ButtonLoop();

#endif /* ARDUINO_BUTTON_H */
