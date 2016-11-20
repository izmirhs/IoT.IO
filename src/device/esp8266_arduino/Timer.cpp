#include "Timer.h"
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

void TIMERInit(uint32_t period)
{
  os_timer_setfn(&localTimer, timerCallback, NULL);
  os_timer_arm(&localTimer, period, true);
  localTimerTick = false;
}

void TIMERLoop()
{
  if(localTimerTick)
  {
    /* Periodic event in here! */
    localTimerTick = false;
  }
}

