#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
// put function declarations here:
int myFunction(int, int);
#define SCL 0
#define SDA 1

// U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /*clock=*/SCL, /*data=*/SDA, /*reset=*/U8X8_PIN_NONE);
// use hardware I2C
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /*reset=*/U8X8_PIN_NONE, /*clock=*/SCL, /*data=*/SDA);

int progess = 0;

void setup()
{
  // put your setup code here, to run once:
  u8g2.begin();
  u8g2.enableUTF8Print();

  Serial.begin(115200);
}

void loop()
{
  u8g2.setFont(u8g2_font_unifont_t_chinese2);
  u8g2.setFontDirection(0);

  u8g2.clearBuffer();

  u8g2.firstPage();
  do
  {
    u8g2.drawFrame(0, 10, 128, 20);
    u8g2.drawUTF8(2, 60, "升温度高ing");
    u8g2.drawBox(0, 10, progess, 20);

  } while (u8g2.nextPage());

  if (progess < 128)
  {
    progess++;
  }
  else
  {
    progess = 0;
  }
  // delay(300);

  // put your main code here, to run repeatedly:
  Serial.println("is running");
}

// put function definitions here:

void display_menu()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_chinese2);
  u8g2.setCursor(0, 15);
  u8g2.print("Hello xiaojiang");
  u8g2.setCursor(0, 40);
  u8g2.print("hello的的的你好!");
  u8g2.sendBuffer();
}