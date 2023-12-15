#ifndef __GLOBAL_H__
#define __GLOBAL_H__

struct THDate
{
    float SHT40Temp, SHT40Humi;
    float MAX6675Temp;
};

extern THDate pfData;

#endif