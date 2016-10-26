#ifndef ARDUINO_GLOBAL_H
#define ARDUINO_GLOBAL_H

#define USE_SERIAL Serial
#define USE_DRAGON_BOARD
#define USE_NODEMCU_BOARD

#define MAX_FILE_ATTR_LEN 64
#define MAX_FILE_SIZE     512
#define MAX_JSON_ATTR_LEN 64
#define JSON_BUF_SIZE     256

static const int pinMap[10] = {16, 5, 4, 0, 14, 12, 13, 15, 3, 1};

#endif /* ARDUINO_GLOBAL_H */
