#ifndef PWM_H
#define PWM_H
#include <Arduino.h>

#define LED_PIN 9

#define FREQ 1200     // 频率
#define CHANNEL 4     // 通道
#define RESOLUTION 10 // 分辨率
#define BUZZER 12     // 引脚

void PWM_setup();
void PWM_loop();

#endif
