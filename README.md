Arduino Setup for ESP8266 : 

1. Install the Arduino IDE 1.6.4 or greater from : https://www.arduino.cc/en/Main/Software
2. To Install the ESP8266 Board Package, go to : File->Preferences from menu.
3. Add http://arduino.esp8266.com/stable/package_esp8266com_index.json to Additional Boards Manager URLs. 
4. Go to Boards Manager from Tools->Board->Boards Manager.
5. Search for esp8266 and install.
6. Now you are able to select esp8266 as a board from Tools->Board. 
7. Select "Generic ESP8266 Board" as board, 80 MHz as CPU Frequency, 4M (1M SPIFFS) as Flash Size.
8. To be able to write SW on device and get traces, select a proper device path from Port section.
9. For linux users, add your user to the group of dialout to enable serial comm. 

Required Arduino Libraries :

0. To install arduino libraries use Sketch->Include Libraries->Library Manager or Add .ZIP Library.
1. ArduinoJson		: https://github.com/bblanchon/ArduinoJson
2. ArduinoWebSocket	: https://github.com/Links2004/arduinoWebSockets
3. PubSubClient		: https://github.com/knolleary/pubsubclient/
4. ArduinoHTTPClient: https://github.com/milesburton/Arduino-Temperature-Control-Library 
5. OneWire			: https://github.com/PaulStoffregen/OneWire
6. DallasTemperature: https://github.com/milesburton/Arduino-Temperature-Control-Library

WiFi Setup Methods : 

1. Dummy Setup : Write your WiFi credentials under Credentials.h file.
   To enable, define SETUP_DUMMY_CONFIG from Credentials.h.
2. SmartConfig : ESP has a protocol called ESP-TOUCH which floads sub-IP packets via its radio for ease of WiFi setup.
   With this method, WiFi credentials are easily sending to ESP8266 without falling back to AP mode.
   Until getting our own Android App, this app would be used initially : 
   https://play.google.com/store/apps/details?id=com.cmmakerclub.iot.esptouch&hl=tr
   You can compile from source : https://github.com/EspressifApp/EsptouchForAndroid
   To enable, define SETUP_SMART_CONFIG from Credentials.h.
3. WebServer Setup : Device gets in AP mode and starts a WebServer on a given IP. 
   Handles POSTed Wifi credential and user data and process them.
   To enable, define SETUP_WEBSERVER_AP from Credentials.h.
4. When connection gets succeeded, they all will be stored on the filesystem.

Using Postman to send WiFi credentials to device's WebServer in AP mode (Demo purpose):

0. Postman is a cool Chrome browser plugin to make HTTP request. It is for demo purpose until we have a user client.
1. We will POST JSON data to the ESP8266 device to handle requests.
2. In AP mode, we have IP address of 192.168.99.1.
3. You need to send below JSON data to set WiFi credentials on board.
4. {type:"APInfo", ssid:YOUR_SSID, pass:YOUR_PASS}
5. Device requires a reboot to left AP mode and connect to WiFi. So send the data below.
6. {type:"APDone"}
 

Data Communication Methods : 

0. Our base supports both MQTT and WebSocket for cloud comm. Contact Cihan Begburs for server credentials.
1. For MQTT, enable PROTOCOL_MQTT define from Global.h.
2. For WebSocket, enable PROTOCOL_WEBSOCKET define from Global.h.

Hardware :

1. Initial DS18B20 OneWire digital sensor implementaiton was added thru the library.
OneWire needs a 4.7K pull-up resistor. Check for the schematics.
2. Relays are able to be controlled via GPIOs 8 & 9.

Factory Reset:

1. A button (currently connected to GPIO 0) was programmed to clear user data such as Wifi Credentials.
2. Need to press more than 3 seconds to fallback in setup mode.
3. A led indicatior will be added to feedback the status. 

