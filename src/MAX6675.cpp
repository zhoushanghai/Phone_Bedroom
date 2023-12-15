// this example is public domain. enjoy!
// https://learn.adafruit.com/thermocouple/

#include "MAX6675_my.h"
#include <max6675.h>
#include <LiquidCrystal.h>
#include <Wire.h>

extern THDate pfData;
/////////////////////////////////////////

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 3;
int gndPin = 2;

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// make a cute degree symbol
uint8_t degree[8] = {140, 146, 146, 140, 128, 128, 128, 128};

void MAX6675_setup()
{
    // use Arduino pins
    pinMode(vccPin, OUTPUT);
    digitalWrite(vccPin, HIGH);
    pinMode(gndPin, OUTPUT);
    digitalWrite(gndPin, LOW);

    Serial.println("MAX6675 test");

    // wait for MAX chip to stabilize
    delay(500);
}

void MAX6675_loop()
{
    float tmepC = thermocouple.readCelsius();
    pfData.MAX6675Temp = tmepC;
    //     // go to line #1
    //     lcd.setCursor(0, 1);
    //     lcd.print(thermocouple.readCelsius());
    // #if ARDUINO >= 100
    //     lcd.write((byte)0);
    // #else
    //     lcd.print(0, BYTE);
    // #endif
    //     lcd.print("C ");
    //     lcd.print(thermocouple.readFahrenheit());
    // #if ARDUINO >= 100
    //     lcd.write((byte)0);
    // #else
    //     lcd.print(0, BYTE);
    // #endif
    //     lcd.print('F');
}