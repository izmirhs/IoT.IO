#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "MQTTConnector.h"
#include "PayloadProcessor.h"
#include "Global.h"
#include "Credentials.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
static const Protocol_t protocol = MQTT;
boolean mqttInitCompleted = false;
String clientId = "ESP8266Client-" + String(ESP.getChipId());
String deviceTopic = "";

void dataCallback(char* topic, byte* payload, unsigned int length)
{
  Serial.printf("Data    : Topic : [%s]\n", topic);
  Serial.printf("Data    : Payload : ");
  for (int i = 0; i < length; i++)
  {
    Serial.printf("%c", (char)payload[i]);
  }
  Serial.printf("\n");
  char response[JSON_BUF_SIZE];
  PAYLOADParse((const char*)payload, protocol, response);
  if(response && strlen(response) && deviceTopic.c_str() && strlen(deviceTopic.c_str()))
  {
    MQTTPublish(deviceTopic.c_str(), response);
  }
  else
  {
    Serial.printf("Error!  : MQTT Data callback. Request connot be processed correctly !!!\n");
  }
}

void performConnect()
{
  uint16_t connection_delay = 5000;
  while (!mqttClient.connected())
  {
    Serial.printf("Trace   : Attempting MQTT connection...\n");
    if (mqttClient.connect(clientId.c_str(), MQTT_USERNAME, MQTT_KEY))
    {
      Serial.printf("Trace   : Connected to Broker.\n");
      char topicPath[MAX_TOPIC_LEN];
      memset(topicPath, 0, MAX_TOPIC_LEN);
      snprintf(topicPath, MAX_TOPIC_LEN, "%s%s", MQTT_TOPIC_ROOT, WiFi.macAddress().c_str()); 
      
      if(MQTTSubscribe(topicPath))
      {
        Serial.printf("Trace   : Subscribed to the topic : %s\n", topicPath);
      }
      else
      {
        Serial.printf("Error!  : Failed to subscribe to topic : %s. Too bad! Reconnect to MQTT.\n", topicPath);
        MQTTDisconnect();
        delay(connection_delay);
      }
    }
    else
    {
      Serial.printf("Error!  : MQTT Connect failed, rc= %d\n", mqttClient.state());
      Serial.printf("Trace   : Try again in %d msec.\n", connection_delay);
      delay(connection_delay);
      /* Perform some check in here to recover or fallback to setup. */
    }
  }
}

/* Non-JSON data publishment. */
boolean MQTTPublish(const char* topic, const char* payload)
{
  boolean retval = false;
  if (mqttClient.connected())
  {
    retval = mqttClient.publish(topic, payload);
  }
  
  return retval;
}

/* JSON type data publishment. */
boolean MQTTPublish(const char* topic, const char* type, const char* data)
{
  boolean retval = false;
  if (mqttClient.connected())
  {
    char request[JSON_BUF_SIZE];
    if(PAYLOADCompose(type, data, request))
    {
      retval = mqttClient.publish(topic, request); 
    }
  }
  
  return retval;
}

boolean MQTTSubscribe(const char* topicToSubscribe)
{
  boolean retval = false;
  if (mqttClient.connected())
  {
    retval = mqttClient.subscribe(topicToSubscribe);
  }
  return retval;
}

boolean MQTTConnected()
{
  return mqttClient.connected();
}

void MQTTSetTopic(const char* topic)
{
    deviceTopic = topic;
}

void MQTTInit()
{
  mqttClient.setServer(MQTT_BROKER, MQTT_BROKER_PORT);
  mqttClient.setCallback(dataCallback);
  mqttInitCompleted = true;
}

void MQTTDisconnect()
{
  mqttClient.disconnect();  
}

void MQTTLoop()
{
  if(mqttInitCompleted)
  {
    if (!mqttClient.connected())
    {
      performConnect();
    }
    mqttClient.loop();
  }
}
