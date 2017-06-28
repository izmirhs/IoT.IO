#ifndef ARDUINO_MQTTCONNECTOR_H
#define ARDUINO_MQTTCONNECTOR_H

#include <Arduino.h>

#define MQTT_TOPIC_ROOT   "IoT.IO/devices/"
#define MQTT_TYPE_INIT    "mqtt_init"

#define MAX_TOPIC_LEN     128

void    MQTTInit();
void    MQTTLoop();
boolean MQTTPublish(const char* topic, const char* payload);
boolean MQTTPublish(const char* topic, const char* type, const char* data);
boolean MQTTSubscribe(const char* topicToSubscribe);
boolean MQTTConnected();
void    MQTTSetTopic(const char* topic);
void    MQTTDisconnect();

#endif /* ARDUINO_MQTTCONNECTOR_H */
