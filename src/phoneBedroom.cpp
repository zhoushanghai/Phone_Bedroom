#include "phoneBedroom.h"
#include "KEY.h"

extern int keySta;
extern int timeCnt;

#define ENUM_ITEM(ITEM) ITEM,
#define ENUM_STRING(ITEM) #ITEM,

#define CHARGER_STATUS_ENUM(STATUS)                              \
    STATUS(CS_INIT)         /*设备初始化*/                  \
    STATUS(CS_IDLE)         /*空闲(等待模式设置)状态*/ \
    STATUS(CS_PREPRE_START) /*开始准备状态*/               \
    STATUS(CS_PREPRE_END)   /*准备结束状态*/               \
    STATUS(CS_WAIT_PHONE)   /*等待手机放入*/               \
    STATUS(CS_CHARGING)     /*开始充电*/                     \
    STATUS(CS_CHARGED)      /*充电结束*/                     \
    STATUS(CS_PAUSE)        /*暂停*/                           \
    STATUS(CS_NUM)          /*状态总数(无效状态)*/

typedef enum
{
    CHARGER_STATUS_ENUM(ENUM_ITEM)
} CHARGER_STATUS;

const char *charger_status_name[] = {
    CHARGER_STATUS_ENUM(ENUM_STRING)};

CHARGER_STATUS chargerStatus = CS_INIT;
CHARGER_STATUS nowChargerStatus = CS_INIT;
CHARGER_STATUS lastChargerStatus = CS_INIT;

CHARGER_STATUS charger_do_init()
{

    CHARGER_STATUS nextStatus = CS_IDLE;
    return nextStatus;
}

CHARGER_STATUS charger_do_idle()
{
    CHARGER_STATUS nextStatus = CS_IDLE;
    if (keySta == S_key)
    {
        nextStatus = CS_PREPRE_START;
    }

    return nextStatus;
}

CHARGER_STATUS charger_do_prepare_start()
{
    CHARGER_STATUS nextStatus = CS_PREPRE_START;
    if (keySta == S_key)
    {
        nextStatus = CS_PREPRE_END;
    }
    if (keySta == L_key)
    {
        nextStatus = CS_IDLE;
    }
    return nextStatus;
}

CHARGER_STATUS charger_do_prepare_end()
{
    CHARGER_STATUS nextStatus = CS_WAIT_PHONE;
    /// 这里只是一个测试，因为还没有灰度传感器
    if (keySta == S_key)
    {
        nextStatus = CS_CHARGING;
    }
    if (keySta == L_key)
    {
        nextStatus = CS_IDLE;
    }
    return nextStatus;
}
////////////////this is also will change/////////////////////////////////////////////////////////
CHARGER_STATUS charger_do_wait_phone()
{
    CHARGER_STATUS nextStatus = CS_WAIT_PHONE;
    if (keySta == S_key)
    {
        nextStatus = CS_CHARGING;
    }
    if (keySta == L_key)
    {
        nextStatus = CS_IDLE;
    }
    return nextStatus;
}

CHARGER_STATUS charger_do_charging()
{
    CHARGER_STATUS nextStatus = CS_CHARGING;
    if (keySta == S_key)
    {
        nextStatus = CS_CHARGED;
    }
    if (keySta == D_key)
    {
        nextStatus = CS_PAUSE;
    }

    // if (nextStatus != nowchargerStatus)
    // {
    //     timeCnt = 0;
    // }

    if (timeCnt >= 1000)
    {
        nextStatus = CS_CHARGED;
    }

    return nextStatus;
}

CHARGER_STATUS charger_do_charged()
{
    CHARGER_STATUS nextStatus = CS_CHARGED;
    if (keySta == S_key)
    {
        nextStatus = CS_CHARGING;
    }

    if (timeCnt >= 1000)
    {
        nextStatus = CS_PREPRE_START;
    }

    return nextStatus;
}

CHARGER_STATUS charger_do_pause()
{
    CHARGER_STATUS nextStatus = CS_PAUSE;
    if (keySta == D_key)
    {
        nextStatus = CS_CHARGING;
    }
    if (keySta == L_key)
    {
        nextStatus = CS_IDLE;
    }
    return nextStatus;
}

void charger_run_loop()
{
    switch (chargerStatus)
    {
    case CS_INIT:
        chargerStatus = charger_do_init();
        break;
    case CS_IDLE:
        chargerStatus = charger_do_idle();
        break;
    case CS_PREPRE_START:
        chargerStatus = charger_do_prepare_start();
        break;
    case CS_PREPRE_END:
        chargerStatus = charger_do_prepare_end();
        break;
    case CS_WAIT_PHONE:
        chargerStatus = charger_do_wait_phone();
        break;
    case CS_CHARGING:
        chargerStatus = charger_do_charging();
        break;
    case CS_CHARGED:
        chargerStatus = charger_do_charged();
        break;
    case CS_PAUSE:
        chargerStatus = charger_do_pause();
        break;
    default:
        break;
    }

    if (nowChargerStatus != chargerStatus)
    {
        Serial.print("Charger Status: ");
        Serial.println(charger_status_name[chargerStatus]);
        lastChargerStatus = nowChargerStatus;
        nowChargerStatus = chargerStatus;

        timeCnt = 0;
    }
}
