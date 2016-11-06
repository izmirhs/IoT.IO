#ifndef ARDUINO_WEBSERVER_H
#define ARDUINO_WEBSERVER_H

#include <Arduino.h>

#define HTTP_OK             200
#define HTTP_NOT_FOUND      404

#define HTTP_CONTENT_JSON   "application/json"
#define HTTP_CONTENT_TEXT   "text/plain"

#define HTTP_SERVER_PORT    80
#define HTTP_SERVER_PATH    "/"

void WEBInit();
void WEBStop();
void WEBLoop();

#endif /* ARDUINO_WEBSERVER_H */
