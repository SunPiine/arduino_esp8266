#include <ESP8266WiFi.h>
#include "WiFilLink_class.h"
const char *name = "TP-LINK_F196";
const char *password = "z19981998";
WiFiLink mywifi(name, password);
WiFiServer myserver(80);
void setup()
{
  mywifi.linking();
  myserver.begin();
  Serial.println(F("服务开始"));
}

void loop()
{
  myserver.begin();
  mywifi.relinking();
  WiFiClient client;
  do
  {
    client = myserver.available();
  } while (!client); //如果未连接就重新循环监测
  client.setTimeout(1000);
  String req = client.readStringUntil('\r');
  Serial.println(F("请求: "));
  Serial.println(req);
  //匹配 请求-->信号变量
  if (req.indexOf(F("/gpio/0")) != -1)
  {
    //如果/gpio/0在请求内容中，发出开灯的信号
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
  else if (req.indexOf(F("/gpio/1")) != -1)
  {
    digitalWrite(LED_BUILTIN, HIGH); // 关
  }
  else
  {
    Serial.println(F("无效请求"));
  }
  //读取或忽略余下的请求内容
  while (client.available())
  {
    client.read();
  }

  //向客户端发送回答，HTML网页代码内容
  //nagle算法会将它们分组为一个数据包
  client.print(F("<!DOCTYPE html>"))
  client.print(F("<head>\r\n<meta charset='utf-8'/>\r\n<title>测试控制灯</title>\r\n"));
  client.print(F("<style type='text/css'>.state{text-align:center;font-size:80px;}"));
  client.print(F(".on{text-align:center;font-size:200px;alink='#1a9e5f'}.off{text-align:center;font-size:200px;alink='#da4f43'}"));
  client.print(F("</style><body><div class='state'>灯状态："));
  client.print((!digitalRead(LED_BUILTIN)) ? F("开</div>") : F("关</div>"));
  client.print(F("<br><br><div class='on'><a href='http://")); //<br>换行
  client.print(WiFi.localIP());
  client.print(F("/gpio/0'>开</a></div><br><br><div class='off'><a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/1'>关</a></div></body></html>"));
  // 客户端实际上将被“刷新”,然后断开连接
  // 当函数返回并且“客户端”对象被销毁时
  // 刷新=确保书面数据被服务端接收
  Serial.println(F("客户端已挂起！"));
}
