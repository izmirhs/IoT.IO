#ifndef ARDUINO_SETUPCONTROLLER_H
#define ARDUINO_SETUPCONTROLLER_H

#include <Arduino.h>

/* TODO: Need return values in here! */
void SETUPConfigStart();
void SETUPConfigStop();
boolean SETUPConfigCheck(char * ssid, char * pass);

#endif /* ARDUINO_SETUPCONTROLLER_H */
