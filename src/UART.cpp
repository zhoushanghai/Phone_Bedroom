#include "UART.h"

void pfData_UART()
{

    Serial.print("MAX6675 C = ");
    Serial.println(pfData.MAX6675Temp);

    Serial.print("Temperature: ");
    Serial.print(pfData.SHT40Temp);
    Serial.println(" degrees C");
    Serial.print("Humidity: ");
    Serial.print(pfData.SHT40Humi);
    Serial.println("% rH");
};