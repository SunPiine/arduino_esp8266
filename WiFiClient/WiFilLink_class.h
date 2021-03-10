/***** 
#include <ESP8266WiFi.h>
#include "WiFilLink_class.h"
const char *name = "TP-LINK_F196";
const char *password = "z19981998";
//增加，捕获输入新WiFi的函数2021-03-10
WiFiLink mywifi(name, password);
void setup()
{
  mywifi.linking();
}

void loop()
{
  mywifi.relinking();
  delay(2000);
}

 *****/

#pragma once
#include <ESP8266WiFi.h>
class WiFiLink
{
private:
    const char *password;
    const char *name;
    bool linktype;

public:
    WiFiLink() = default;
    WiFiLink(const char *myn, const char *myp) : password(myp), name(myn)
    {
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.begin(9600);
        WiFi.mode(WIFI_STA);
    }
    void relinking(void) //重连函数可与if语句共同使用，先通过调用linktype成员判断是否在线
    {
        linked(); //一般均需要这一函数，以保证连接有效性
        if (!linktype)
        {
            WiFi.disconnect();
            Serial.println(" ");
            Serial.print(F("开始重连"));
            linking();
        }
    }

    bool linked(void) //返回是否连接上
    {
        linktype = (WiFi.status() == WL_CONNECTED);
        return linktype;
    }
    void linking(void) //进行连接操作，最后输出本地IP地址
    {
        WiFi.begin(name, password);
        Serial.println(" ");
        Serial.print(F("开始连接"));
        do
        {
            bool ledtype = HIGH;
            bool change = false;
            String Wifiname;
            String Wifipassword;
            ledtype = digitalRead(LED_BUILTIN);
            digitalWrite(LED_BUILTIN, !ledtype);
            Serial.print(".");
            if (Serial.available())
            //Serial.available() 用来检查串口接受是否准备好，
            // 即是否有数据已经发送到单片机的Flush，之后再执行动作
            // 触发时flush已经装填，紧接着的读取动作会读取
            {
                get_input(Wifiname, Wifipassword);
                WiFi.begin(Wifiname.c_str(), Wifipassword.c_str());
                Serial.println(" ");
                Serial.print(F("开始连接"));
            }
            delay(500);
        } while (WiFi.status() != WL_CONNECTED);
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println(" ");
        Serial.println(F("链接成功！"));
        Serial.println(WiFi.localIP());
    }
    void get_input(String &n, String &p)
    //从串口获取字符串，并以String引用的形式传出
    {
        Serial.readString();
        Serial.println("输入Wifi Name：");
        while (n.length() == 0)
        {
            n = Serial.readString();
        }
        Serial.println("Wifi Name：");
        Serial.println(n);
        Serial.println("输入Wifi Password：");
        while (p.length() == 0)
        {
            p = Serial.readString();
        }
        Serial.println("Wifi Password：");
        Serial.println(p);
    }
};
