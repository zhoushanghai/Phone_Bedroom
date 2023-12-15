#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Ticker.h> //software timer

#include "PWM.h"
#include "SHT40.h"
#include "MAX6675_my.h"
#include "OLED.h"
// put function declarations here:
void set_flag(int *flag);
int detFlag(int *flag);
// software timer
Ticker oledTimer, sht40Timer, max6675Timer;

int flagOLED = 0, flagSHT40 = 0, flagMAX6675 = 0;

void setup()
{

  Serial.begin(115200);
  OLED096_setup();
  PWM_setup();
  SHT40_setup();
  MAX6675_setup();

  // software timer
  oledTimer.attach_ms(100, set_flag, &flagOLED);
  sht40Timer.attach_ms(50, set_flag, &flagSHT40);
  max6675Timer.attach_ms(200, set_flag, &flagMAX6675);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (detFlag(&flagOLED))
  {
    OLED096_loop();
  }
  if (detFlag(&flagSHT40))
  {
    SHT40_loop();
  }
  if (detFlag(&flagMAX6675))
  {
    MAX6675_loop();
    Serial.println("running");
  }

  // PWM_loop();
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