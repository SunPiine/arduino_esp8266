/***** 
#include <ESP8266WiFi.h>
#include "WiFilLink_class.h"
const char *name = "TP-LINK_F196";
const char *password = "z19981998";
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
            ledtype = digitalRead(LED_BUILTIN);
            digitalWrite(LED_BUILTIN, !ledtype);
            Serial.print(".");
            delay(500);
        } while (WiFi.status() != WL_CONNECTED);
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println(" ");
        Serial.println(F("链接成功！"));
        Serial.println(WiFi.localIP());
    }
};
