#ifndef ARDUINO_GLOBAL_H
#define ARDUINO_GLOBAL_H

#define Printf            Serial.printf
#define SERIAL_BAUD_RATE  9600
#define TIMER_PERIOD      60 * 1000

typedef enum Protocol
{
  WebSocket = 0,
  MQTT,
  HTTP
}Protocol_t;

/* Board Definitions */
#define USE_NODEMCU_BOARD
//#define USE_GENERIC_ESP8266
//#define USE_DRAGON_BOARD

/* Setup Method Definitions :
 * SETUP_SMART_CONFIG : ESP-TOUCH protocol to send mobile device's SSID to ESP.
 * SETUP_DUMMY_CONFIG : A constant credential gonna be booted up.
 * SETUP_WEBSERVER_AP : A webserver runs on ESP in AP mode to handle user requests and credentials.
 */
//#define SETUP_SMART_CONFIG
//#define SETUP_DUMMY_CONFIG
#define SETUP_WEBSERVER_AP

/* Protocol Definitions */
#define PROTOCOL_WEBSOCKET
//#define PROTOCOL_MQTT

/* IO Definitions */
#define MAX_FILE_ATTR_LEN 64
#define MAX_FILE_SIZE     512
#define MAX_JSON_ATTR_LEN 64
#define JSON_BUF_SIZE     512
#define MAX_IP_LEN        17
#define LEN_TEMP_MAX      6

#endif /* ARDUINO_GLOBAL_H */
