#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "MQTTConnector.h"
#include "PayloadProcessor.h"
#include "Global.h"
#include "Credentials.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
static const Protocol_t protocol = HTTP;
boolean mqttInitCompleted = false;
String clientId = "ESP8266Client-" + String(ESP.getChipId());

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
      /* Example of non-JSON publish and subscribe. */
      MQTTDeliver(MQTT_TOPIC_INIT, String(ESP.getChipId()).c_str());
      mqttClient.subscribe(MQTT_TOPIC_SENSOR);
      mqttClient.subscribe(MQTT_TOPIC_RELAY);
      /* Subscribe and publish to JSON topic.  */
      mqttClient.subscribe(MQTT_TOPIC_JSON);
      MQTTDeliver(MQTT_TOPIC_JSON, MQTT_TYPE_INIT, String(ESP.getChipId()).c_str());
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
boolean MQTTDeliver(const char* topic, const char* payload)
{
  boolean retval = false;
  if (mqttClient.connected())
  {
    retval = mqttClient.publish(topic, payload);
  }
  
  return retval;
}

/* JSON type data publishment. */
boolean MQTTDeliver(const char* topic, const char* type, const char* data)
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

void MQTTInit()
{
  mqttClient.setServer(MQTT_BROKER, MQTT_BROKER_PORT);
  mqttClient.setCallback(dataCallback);
  mqttInitCompleted = true;
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
