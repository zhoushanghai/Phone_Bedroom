#ifndef __KEY_H__
#define __KEY_H__

#include <Arduino.h>
#include <Wire.h>
#include "global.h"

#define BUTTON_PIN 4

#define N_key 0 // 无键
#define S_key 1 // 单键
#define D_key 2 // 双键
#define L_key 3 // 长键

unsigned char key_read(void);
void key_setup();

/*
// 定义状态机状态
enum ButtonState
{
    IDLE,
    PRESSED,
    LONG_PRESS,
    DOUBLE_CLICK,
    DEBOUNCE
};

void key_setup();
enum ButtonState detButton();
void checkButton();
*/

#endif
