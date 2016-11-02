#ifndef ARDUINO_MQTTCONNECTOR_H
#define ARDUINO_MQTTCONNECTOR_H

#include <Arduino.h>

#define MQTT_TOPIC_JSON    "/iot/json"
#define MQTT_TOPIC_INIT    "/iot/text/init"
#define MQTT_TOPIC_SENSOR  "/iot/text/sensor"
#define MQTT_TOPIC_RELAY   "/iot/text/relay"

#define MQTT_TYPE_INIT     "mqtt_init"

void MQTTInit();
void MQTTLoop();
boolean MQTTDeliver(const char* topic, const char* payload);
boolean MQTTDeliver(const char* topic, const char* type, const char* data);

#endif /* ARDUINO_MQTTCONNECTOR_H */
