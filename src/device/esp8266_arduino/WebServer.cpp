#include <ESP8266WebServer.h>

#include "WebServer.h"
#include "PayloadProcessor.h"

ESP8266WebServer webServer(HTTP_SERVER_PORT);
static const Protocol_t protocol = HTTP;
boolean webServerInitCompleted = false;

void handleRequest()
{
  if(webServer.args() == 1 && webServer.arg(0).c_str())
  {
    char response[JSON_BUF_SIZE];
    PAYLOADParse(webServer.arg(0).c_str(), protocol, response);

    if(strlen(response))
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
    Serial.printf("Error!  : WebwebServer. Not a POSTed data!\n");
  }
}

void handleNotFound()
{
  char *message = "Not Found\n";

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
