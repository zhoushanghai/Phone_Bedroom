#include "PWM.h"

#define FREQ 50       // Ƶ��
#define CHANNEL 4     // ͨ��
#define RESOLUTION 10 // �ֱ���
#define LED 12        // LED ����

void PWM_setup()
{
    ledcSetup(CHANNEL, FREQ, RESOLUTION); // ����ͨ��
    ledcAttachPin(LED, CHANNEL);          // ��ͨ�����Ӧ����������
}

void PWM_loop()
{

    // // �𽥱���
    // for (int i = 0; i < pow(2, RESOLUTION); i++)
    // {
    //     ledcWrite(CHANNEL, i); // ���PWM
    //     delay(5);
    // }

    // // �𽥱䰵
    // for (int i = pow(2, RESOLUTION) - 1; i >= 0; i--)
    // {
    //     ledcWrite(CHANNEL, i); // ���PWM
    //     delay(5);
    // }
}
