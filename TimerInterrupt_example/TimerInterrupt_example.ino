#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0

#include "SAMDTimerInterrupt.h"

#define LED_BUILTIN       13
#define TIMER0_INTERVAL_MS        15000   //1000


SAMDTimer ITimer0(TIMER_TCC);

void TimerHandler0()
{
  unsigned long current_time = millis();
  Serial.println(current_time);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  while (!Serial);

  delay(100);

  // Interval in microsecs
  ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0);
}

void loop(){}
