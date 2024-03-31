#include "phoneBedroom.h"
#include "KEY.h"

extern int keySta;
extern int timeCnt;
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

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
    if (keySta == D_key)
    {
        nextStatus = CS_PAUSE;
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
    if (keySta == D_key)
    {
        nextStatus = CS_PAUSE;
    }
    return nextStatus;
}

CHARGER_STATUS charger_do_prepare_end()
{
    CHARGER_STATUS nextStatus = CS_WAIT_PHONE;

    if (!digitalRead(DETECT_PIN))
    {
        nextStatus = CS_CHARGING;
    }
    if (keySta == L_key)
    {
        nextStatus = CS_IDLE;
    }
    if (keySta == D_key)
    {
        nextStatus = CS_PAUSE;
    }

    return nextStatus;
}

CHARGER_STATUS charger_do_wait_phone()
{
    CHARGER_STATUS nextStatus = CS_WAIT_PHONE;
    if (!digitalRead(DETECT_PIN))
    {
        nextStatus = CS_CHARGING;
    }
    if (keySta == L_key)
    {
        nextStatus = CS_IDLE;
    }
    if (keySta == D_key)
    {
        nextStatus = CS_PAUSE;
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
    if (keySta == L_key)
    {
        nextStatus = CS_IDLE;
    }
    // if (nextStatus != nowchargerStatus)
    // {
    //     timeCnt = 0;
    // }

    if (timeCnt >= 10)
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
        nextStatus = CS_IDLE;
    }
    if (keySta == L_key)
    {
        nextStatus = CS_IDLE;
    }

    if (timeCnt >= 10)
    {
        nextStatus = CS_IDLE;
    }
    if (keySta == D_key)
    {
        nextStatus = CS_PAUSE;
    }

    return nextStatus;
}

CHARGER_STATUS charger_do_pause()
{
    CHARGER_STATUS nextStatus = CS_PAUSE;
    if (keySta == D_key)
    {
        nextStatus = lastChargerStatus;
    }
    if (keySta == L_key)
    {
        nextStatus = CS_IDLE;
    }
    return nextStatus;
}

void charger_run_loop()
{
    static int timeCntShow = 0;
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

    if (timeCntShow++ % 10 == 0)
    {
        switch (chargerStatus)
        {
        case CS_INIT:

            break;
        case CS_IDLE:

            if (nowChargerStatus != lastChargerStatus)
            {
                u8g2.clearBuffer();
                ////////////菜单////////////////
                u8g2.setCursor(0, 14);
                u8g2.print("开始 准备 等待 充电 完成");
                u8g2.setDrawColor(0);
                u8g2.setCursor(0, 14);
                u8g2.print("开始");
                u8g2.setDrawColor(1);
                u8g2.drawHLine(0, 16, 128);
                ///////////显示内容/////////////////

                u8g2.setCursor(30, 45);
                u8g2.print("开始充电");
                u8g2.sendBuffer();
            }

            break;
        case CS_PREPRE_START:
            if (nowChargerStatus != lastChargerStatus)
            {
                u8g2.clearBuffer();
                ////////////菜单////////////////
                u8g2.setCursor(0, 14);
                u8g2.print("开始 准备 等待 充电 完成");
                u8g2.setDrawColor(0);
                u8g2.setCursor(40, 14);
                u8g2.print("准备");
                u8g2.setDrawColor(1);
                u8g2.drawHLine(0, 18, 128);
                ///////////显示内容/////////////////
                u8g2.setCursor(14, 40);
                u8g2.print("做好事前准备");

                u8g2.sendBuffer();
            }
            break;
        case CS_PREPRE_END:

            break;
        case CS_WAIT_PHONE:
            if (nowChargerStatus != lastChargerStatus)
            {
                u8g2.clearBuffer();
                ////////////菜单////////////////
                u8g2.setCursor(0, 14);
                u8g2.print("开始 准备 等待 充电 完成");
                u8g2.setDrawColor(0);
                u8g2.setCursor(80, 14);
                u8g2.print("等待");
                u8g2.setDrawColor(1);
                u8g2.drawHLine(0, 18, 128);
                ///////////显示内容/////////////////
                u8g2.setCursor(14, 40);
                u8g2.print("等待放入手机");

                u8g2.sendBuffer();
            }
            break;
        case CS_CHARGING:

            u8g2.clearBuffer();
            ////////////菜单////////////////
            u8g2.setCursor(0, 14);
            u8g2.print("准备 等待 充电 完成");
            u8g2.setDrawColor(0);
            u8g2.setCursor(80, 14);
            u8g2.print("充电");
            u8g2.setDrawColor(1);
            u8g2.drawHLine(0, 18, 128);
            ///////////显示内容/////////////////
            u8g2.setCursor(30, 48);
            u8g2.print("充电ing");
            static int boxlong = 0;
            u8g2.drawFrame(22 + 3, 30, 70, 26);
            u8g2.drawBox(92 + 3, 39, 6, 8);

            u8g2.drawBox(22 + 3, 30, boxlong, 26);

            u8g2.sendBuffer();

            if (boxlong < 70)
            {
                boxlong += 2;
            }
            else
            {
                boxlong = 0;
            }

            break;
        case CS_CHARGED:
            if (nowChargerStatus != lastChargerStatus)
            {
                u8g2.clearBuffer();
                ////////////菜单////////////////
                u8g2.setCursor(0, 14);
                u8g2.print("等待 充电 完成");
                u8g2.setDrawColor(0);
                u8g2.setCursor(80, 14);
                u8g2.print("完成");
                u8g2.setDrawColor(1);
                u8g2.drawHLine(0, 18, 128);
                ///////////显示内容/////////////////
                u8g2.setCursor(30, 40);
                u8g2.print("充电完成");

                u8g2.sendBuffer();
            }
            break;
        case CS_PAUSE:
            if (nowChargerStatus != lastChargerStatus)
            {
                u8g2.clearBuffer();
                ////////////菜单////////////////
                u8g2.setCursor(0, 14);
                u8g2.print("开始 准备 等待 充电 完成");
                u8g2.setDrawColor(0);
                u8g2.setCursor(80, 14);
                u8g2.print("等待");
                u8g2.setDrawColor(1);
                u8g2.drawHLine(0, 18, 128);
                ///////////显示内容/////////////////
                u8g2.clearBuffer();
                u8g2.drawRFrame(15, 5, 98, 54, 5);
                u8g2.drawBox(10 + 40, 10 + 4, 9, 36);
                u8g2.drawBox(10 + 40 + 6 + 16, 10 + 4, 9, 36);
                u8g2.sendBuffer();
            }
            break;
        default:
            break;
        }
    }

    if (nowChargerStatus != chargerStatus)
    {
        Serial.print("Charger Status: ");
        Serial.println(charger_status_name[chargerStatus]);
        lastChargerStatus = nowChargerStatus;
        nowChargerStatus = chargerStatus;

        timeCnt = 0;

        // u8g2.clearDisplay();
    }
}
