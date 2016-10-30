#include <Arduino.h>
#include "NetworkAdapter.h"
#include "Global.h"

void HWInit()
{
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, INPUT);
  delay(10);
  
  USE_SERIAL.begin(9600);
  USE_SERIAL.setDebugOutput(true);
  delay(10);
}

void setup() 
{
  HWInit();
  NETBegin();
}

void loop() 
{
  NETLoop();
}
