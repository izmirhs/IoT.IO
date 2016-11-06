#include "Hardware.h"
#include "FileOrganizer.h"
#include "Global.h"

short hw_delay = 10;
int   btn_current = 0;
long  btn_millis_held = 0;
long  btn_secs_held = 0;
long  btn_prev_secs_held = 0;
byte  btn_previous = HIGH;
short btn_debouncing = 50;
short btn_debounce_threshold = 200;
unsigned long btn_first_time = 0;

void ButtonInit()
{
#ifdef USE_NODEMCU_BOARD
  pinMode(pinMap[3], INPUT);
  /* NOTE: To work with pull-ups. */
  digitalWrite(pinMap[3], HIGH);
#elif defined(USE_DRAGON_BOARD)
  pinMode(pinMap[4], INPUT);
#else
  pinMode(pinMap[4], INPUT);
#endif
}

void LedInit()
{

}

void GPIOInit()
{
#ifdef USE_NODEMCU_BOARD
  pinMode(pinMap[0], OUTPUT);
  pinMode(pinMap[1], OUTPUT);
  pinMode(pinMap[2], OUTPUT);
#elif defined(USE_DRAGON_BOARD)
  pinMode(pinMap[6], OUTPUT);
  pinMode(pinMap[7], OUTPUT);
  pinMode(pinMap[1], OUTPUT);
  pinMode(pinMap[2], OUTPUT);
#else
  pinMode(pinMap[6], OUTPUT);
  pinMode(pinMap[7], OUTPUT);
  pinMode(pinMap[1], OUTPUT);
  pinMode(pinMap[2], OUTPUT);
#endif
  delay(hw_delay);
}

void SerialInit()
{
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  delay(hw_delay);
}

void ButtonLoop()
{
  btn_current = digitalRead(pinMap[3]);
  if (btn_current == LOW && btn_previous == HIGH && (millis() - btn_first_time) > btn_debounce_threshold) 
  {
    btn_first_time = millis();
  }

  btn_millis_held = (millis() - btn_first_time);
  btn_secs_held = btn_millis_held / 1000;

  if (btn_millis_held > btn_debouncing)
  {
    if (btn_current == LOW && btn_secs_held > btn_prev_secs_held)
    {
      Serial.printf("One second event!\n");
    }

    if (btn_current == HIGH && btn_previous == LOW) 
    {
      if (btn_secs_held <= 0)
      {
        Serial.printf("Pressed for less then 1 seconds!\n");
      }
      if (btn_secs_held >= 3)
      {
        FSDeleteFile(WIFI_CONFIG_FILE);
        ESP.restart();
      }
    }
  }
  btn_previous = btn_current;
  btn_prev_secs_held = btn_secs_held;
}

void LedLoop()
{
  
}

void HWRestart()
{
  ESP.restart();
}

void HWInit()
{
  GPIOInit();
  ButtonInit();
  SerialInit();
  FSInit();
}

void HWLoop()
{
  ButtonLoop();
  LedLoop();
}
