#include "OLED.h"

#define SCL 0
#define SDA 1

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /*reset=*/U8X8_PIN_NONE, /*clock=*/SCL, /*data=*/SDA);

// use hardware I2C
int progess = 0;

#define MENU_SIZE 3
char *menu[MENU_SIZE] = {"SHT40 Temp:", "SHT40 Humi:", "MAX667Temp:"};

void OLED096_setup()
{
    // put your setup code here, to run once:

    // u8g2 initialization
    u8g2.begin();
    u8g2.enableUTF8Print();
}

void OLED_showData()
{
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.firstPage();
    do
    {
        // 绘制页面内容
        u8g2.drawStr(2, 12, "DATA");
        u8g2.drawHLine(0, 14, 128);
        for (int i = 0; i < MENU_SIZE; i++)
        {
            u8g2.drawStr(5, (i + 2) * 12 + 2, menu[i]);
        }

        u8g2.setCursor(78, (0 + 2) * 12 + 2);
        u8g2.print(pfData.SHT40Temp);
        u8g2.setCursor(78, (1 + 2) * 12 + 2);
        u8g2.print(pfData.SHT40Humi);
        u8g2.setCursor(78, (2 + 2) * 12 + 2);
        u8g2.print(pfData.MAX6675Temp);

    } while (u8g2.nextPage()); // 进入下一页，如果还有下一页则返回 True.
}

void OLED096_loop()
{
    // put your main code here, to run repeatedly:
    u8g2.setFont(u8g2_font_unifont_t_chinese3);
    u8g2.setFontDirection(0);

    u8g2.clearBuffer();

    u8g2.firstPage();
    do
    {
        u8g2.drawFrame(0, 10, 128, 20);
        u8g2.drawUTF8(2, 60, "hi 王海舟");
        u8g2.drawBox(0, 10, progess, 20);

    } while (u8g2.nextPage());

    if (progess < 128)
    {
        progess += 2;
    }
    else
    {
        progess = 0;
    }
}
