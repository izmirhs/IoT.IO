#include <Arduino.h>
#include "NetworkAdapter.h"
#include "Hardware.h"
#include "Global.h"

void setup() 
{
  HWInit();
  NETBegin();
}

void loop() 
{
  NETLoop();
  HWLoop();
}
