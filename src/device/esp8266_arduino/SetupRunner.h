#ifndef ARDUINO_SETUPCONTROLLER_H
#define ARDUINO_SETUPCONTROLLER_H

#include <Arduino.h>

/* SetupController gonna support 4 modes:
 * SMART_CONFIG_SETUP : ESP-TOUCH protocol to send mobile device's SSID to ESP.
 * DUMMY_SETUP        : A constant credential gonna be booted up.
 * WEBSERVER_SETUP    : A webserver runs on ESP to handle user requests and credentials.
 * WEBSOCKET_SETUP    : A websocket server runs on ESP to handle user data.
 */

//#define USE_SMART_CONFIG_SETUP 
#define USE_DUMMY_SETUP

/* Need return values in here! */
void SETUPConfigStart();
void SETUPConfigStop();
boolean SETUPConfigCheck(char * ssid, char * pass);

#endif /* ARDUINO_SETUPCONTROLLER_H */
