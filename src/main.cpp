#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Ticker.h> //software timer
#include "global.h"

#include "PWM.h"
#include "OLED.h"
#include "UART.h"
#include "KEY.h"
#include "phoneBedroom.h"

// ButtonState keySta = IDLE;

int keySta = N_key;
int timeCnt = 0;
// int

// put function declarations here:
void set_flag(int *flag);
int detFlag(int *flag);
void countTime();
// software timer
Ticker oledTimer, uartTimer, keyTimer, countTimer, chargerTimer;

int flagOLED = 0, flagUART = 0, flagKey = 0, flagBuzzer = 0, flagUnBuzzer = 0;

THDate pfData;

void setup()
{

  Serial.begin(115200);
  OLED096_setup();
  PWM_setup();
  key_setup();

  // software timer
  oledTimer.attach_ms(100, set_flag, &flagOLED);

  uartTimer.attach_ms(1000, set_flag, &flagUART);

  keyTimer.attach_ms(10, set_flag, &flagKey);

  countTimer.attach(1, countTime);

  // chargerTimer.attach_ms(10, charger_run_loop);
}

void loop()
{
  // put your main code here, to run repeatedly:

  if (detFlag(&flagOLED))
  {
    // OLED096_loop();
    // OLED_showData();
  }
  if (detFlag(&flagUART))
  {
    // Serial.println("running");
    // pfData_UART();
  }
  if (detFlag(&flagKey))
  {
    keySta = key_read();
    charger_run_loop();
    switch (keySta)
    {
    case S_key:
      Serial.println("Pressed");
      flagBuzzer = 1;
      break;
    case L_key:
      Serial.println("Long Press");
      flagBuzzer = 1;
      break;
    case D_key:
      Serial.println("Double Click");
      flagBuzzer = 1;
      break;
    default:
      break;
    }

    // buzeer
    if (flagBuzzer)
    {
      static int i = 0;
      if (i == 0)
      {
        ledcWrite(CHANNEL, 1500); // 打开蜂鸣器
      }
      if (i++ > 5)
      {
        i = 0;
        flagBuzzer = 0;
        flagUnBuzzer = 1;
      }
    }
    if (detFlag(&flagUnBuzzer))
    {
      ledcWrite(CHANNEL, 0); // 关闭蜂鸣器
    }
  }
}

// put function definitions here:
void set_flag(int *flag)
{
  *flag = 1;
}
// detect flag
int detFlag(int *flag)
{
  if (*flag == 1)
  {
    *flag = 0;
    return 1;
  }
  else
  {
    return 0;
  }
}

void countTime()
{
  timeCnt++;
}