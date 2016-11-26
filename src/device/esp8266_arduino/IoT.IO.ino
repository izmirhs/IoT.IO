#include <Arduino.h>
#include "NetworkAdapter.h"
#include "Hardware.h"
#include "Timer.h"
#include "Global.h"

void setup() 
{
  HWInit();
  NETBegin();
  TMRInit(TIMER_PERIOD);
}

void loop() 
{
  NETLoop();
  HWLoop();
  TMRLoop();
}
