#ifndef ARDUINO_SETUPRUNNER_H
#define ARDUINO_SETUPRUNNER_H

#include <Arduino.h>

/* TODO: Need return values in here! */
void SETUPConfigStart();
void SETUPConfigStop();
boolean SETUPConfigCheck(char * ssid, char * pass);

#endif /* ARDUINO_SETUPRUNNER_H */
