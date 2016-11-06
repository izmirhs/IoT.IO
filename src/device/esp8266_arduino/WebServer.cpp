#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "WebServer.h"
#include "PayloadProcessor.h"

ESP8266WebServer webServer(HTTP_SERVER_PORT);
boolean webServerInitCompleted = false;

void handleRequest()
{
  String message = "";
  for (uint8_t i = 0; i < webServer.args(); i++)
  {
    message += webServer.argName(i) + ": " + webServer.arg(i) + "\n";
  }
  Serial.printf("Trace   : Incoming HTTP request :\n%s\n", message.c_str());

  if(webServer.args() == 1 && webServer.arg(0).c_str())
  {
    PAYLOADParse(webServer.arg(0).c_str());

    /* For now, resend to incoming data payload as response until we parse and process them. */
    
    String response = message.c_str();
    if(response.length())
    {
      webServer.send(HTTP_OK, HTTP_CONTENT_JSON, response);
    }
    else
    {
      Serial.printf("Error!  : WebwebServer. Request connot be processed correctly !!!\n");
    }
  }
  else
  {
    Serial.printf("Error!  : WebwebServer. Not a POSTed JSON!\n");
  }
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += webServer.uri();
  message += "\nArguments: ";
  message += webServer.args();
  message += "\n";
  for (uint8_t i=0; i< webServer.args(); i++)
  {
    message += " " + webServer.argName(i) + ": " + webServer.arg(i) + "\n";
  }
  webServer.send(HTTP_NOT_FOUND, HTTP_CONTENT_TEXT, message);
}

void WEBStop()
{
  webServer.close();
}

void WEBInit()
{
  webServer.on(HTTP_SERVER_PATH, handleRequest);
  webServer.onNotFound(handleNotFound);
  webServer.begin();
  Serial.printf("Trace   : WebwebServer. HTTP webServer started.\n");
  /* Refer to server begin return value for looping. */
  webServerInitCompleted = true;
}

void WEBLoop()
{
  if(webServerInitCompleted)
  {
    webServer.handleClient(); 
  }
}
