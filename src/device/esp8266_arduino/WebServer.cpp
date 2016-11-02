#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "WebServer.h"
#include "PayloadProcessor.h"

ESP8266WebServer webServer(80);
boolean webServerInitCompleted = false;

void handleRequest()
{
  String message = "";
  for (uint8_t i = 0; i < webServer.args(); i++)
  {
    message += webServer.argName(i) + ": " + webServer.arg(i) + "\n";
  }
  Serial.printf("Trace   : Incoming HTTP request :\n%s\n", message.c_str());

  if(webServer.args() == 1)
  {
    PAYLOADParse(message.c_str());
    Serial.printf("Trace   : HTTP Data payload :  %s\n", webServer.arg(0).c_str());

    /* For now, resend to incoming data payload as response until we parse and process them. */
    
    String response = message.c_str();
    if(response.length())
    {
      webServer.send(200, "text/plain", response);
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
  message += "\nMethod: ";
  message += (webServer.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += webServer.args();
  message += "\n";
  for (uint8_t i=0; i< webServer.args(); i++)
  {
    message += " " + webServer.argName(i) + ": " + webServer.arg(i) + "\n";
  }
  webServer.send(404, "text/plain", message);
}

void WEBStop()
{
  webServer.close();
}

void WEBInit()
{
  webServer.on("/", handleRequest);
  webServer.onNotFound(handleNotFound);
  webServer.begin();
  Serial.printf(" Trace   : WebwebServer. HTTP webServer started.\n");
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
