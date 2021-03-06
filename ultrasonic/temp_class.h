#pragma once
#include <OneWire.h>
//使用1 wire读取DS18B20的温度，单一设备
//初始化时引入引脚DQ；TempData myTempData(myDQpin) 构造函数。
//先使用begin()成员再使用ReturnTemp() 返回温度值，摄氏度
using uchar = unsigned char;
class TempData
{
private:
    uchar HT;
    uchar LT;
    uchar DQ;
    int Temp;
    float mrod;
    bool flag;

public:
    TempData() = default;
    TempData(uchar dq) : DQ(dq)
    {
        HT = 0x00;
        LT = 0x00;
        Temp = 0;
        mrod = 0.0;
        flag = false;
    }
    ~TempData(){};
    void begin(void)
    {
        OneWire onewire(this->DQ);
        onewire.reset();        //重置脉冲，命令紧随其后
        onewire.skip();         //只有一个设备时跳过核对芯片号
        onewire.write(0x44, 1); //写入0x44并拉高为高电平
        delayMicroseconds(160);
        onewire.reset();
        onewire.skip();
        onewire.write(0xbe);
        LT = onewire.read();
        HT = onewire.read();
        bool flag = false;
        if (HT > 127)
        {
            HT = ~HT;
            LT = ~LT;
            LT += 0x01;
            flag = true;
        }
        Temp = Temp | HT;
        Temp <<= 8;
        Temp = Temp | LT;
        mrod = Temp * 0.0625;
        mrod=flag ? -mrod : mrod;
    }
    float ReturnTemp(void)
    {
        return mrod;
    }
};
