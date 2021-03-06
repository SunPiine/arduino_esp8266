//初始化时引入引脚echo ,trig ; ultrasonic myultrasonic(myechopin,mytringpin),构造函数
//先使用begin()成员再使用showcm() 返回长度，厘米
//showcm_temp(),返回温度修正的长度，需要温度数值，可以使用temp_class.h 来获取
#pragma once
class ultrasonic
{
private:
    long times;//毫秒
    float cm;
    const int echo, trig;

public:
    ultrasonic() = default;
    ultrasonic(int ieho, int itig) : echo(ieho), trig(itig)
    {
        setup();
    }
    ~ultrasonic(){};
    void setup(void)
    {
        pinMode(echo, INPUT);
        pinMode(trig, OUTPUT);
    }
    void begin(void)
    {
        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        times = pulseIn(echo, HIGH);
    }
    float showcm(void)
    {
        cm = times / 29 / 2;
        return cm;
    }
    float showcm_temp(float temp)
    {
        float c = 332+0.607*temp;//摄氏度优化声速
        cm = ((times * c) /2.0 )/10000.0;
        return cm;
    }
};
