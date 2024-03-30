#include "PWM.h"



void PWM_setup()
{
    ledcSetup(CHANNEL, FREQ, RESOLUTION); // 设置通道
    ledcAttachPin(BUZZER, CHANNEL);       // 将通道与对应的引脚连接

}

void PWM_loop()
{

    // 逐渐变亮
    for (int i = 0; i < pow(2, RESOLUTION); i++)
    {
        ledcWrite(CHANNEL, i); // 输出PWM
        delay(5);
    }

    // 逐渐变暗
    for (int i = pow(2, RESOLUTION) - 1; i >= 0; i--)
    {
        ledcWrite(CHANNEL, i); // 输出PWM
        delay(5);
    }
}
