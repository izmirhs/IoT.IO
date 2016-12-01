#include "Timer.h"
#include "WebSocketConnector.h"
#include "TempSensor.h"
#include "PayloadTypes.h"
#include "Global.h"

/* Catastrophically using symbols from ESP OpenSDK directly. */
extern "C" {
#include "user_interface.h"
}

os_timer_t localTimer;
boolean localTimerTick = false;

void timerCallback(void *pArg)
{
  /* Keep our ISR light! */
  localTimerTick = true;
}

void TMRInit(uint32_t period)
{
  os_timer_setfn(&localTimer, timerCallback, NULL);
  os_timer_arm(&localTimer, period, true);
  /* TODO: Convert it to true for un-delayed first shot. */
  localTimerTick = false;
}

void TMRLoop()
{
  if(localTimerTick)
  { 
    /* Periodic event start! */
    char tempBuffer[LEN_TEMP_MAX];
    if(TEMPGetString(0, tempBuffer))
    {
      WSOCKDeliver(PAYLOAD_DATA_SENSOR, tempBuffer);
    }
    /* Periodic event end! */
    
    localTimerTick = false;
  }
  yield();
}

