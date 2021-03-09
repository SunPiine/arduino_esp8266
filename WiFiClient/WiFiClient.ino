#include <ESP8266WiFi.h>
#include "WiFilLink_class.h"
const char *name = "TP-LINK_F196";
const char *password = "z19981998";
WiFiLink mywifi(name, password);
WiFiServer myserver(80);
void setup()
{
    Serial.begin(9600);
    mywifi.linking();
    myserver.begin();
    Serial.println(" ");
    Serial.println(F("服务开始"));
}
void loop()
{
    myserver.begin();
    WiFiClient client;
    do
    {
        client = myserver.available();
    } while (!client); //如果未连接就重新循环监测
    client.print(R"+*(<!DOCTYPE html>
<html>
<meta name="viewport" content="width=device-width,initial-scale=1" />
<!-- 上一句使得网页宽高和屏幕适应，结合calc 和 100vw/int 百分比像素，int越小px值越大\
 100vw/int=屏幕宽/需要px-->

<head>
    <title>ON+OFF</title>
</head>
<style>
    .whitebutton {
        text-align: center;
        width: calc(100vw / 2);
        height: calc(100vw / 2);
        font-size: calc(100vw / 15);
        border-radius: 50%;
        outline: none;
        background-color: white;
        box-shadow: 0px, 10px, 10px, 0px rgba(255, 255, 255, 0.336);
    }

    .blackbutton {
        text-align: center;
        width: calc(100vw / 2);
        height: calc(100vw / 2);
        font-size: calc(100vw / 15);
        color:white;
        border-radius: 50%;
        outline: none;
        background-color: black;
        box-shadow: 0px, 10px, 10px, 0px rgba(255, 255, 255, 0.336);
    }

    .div {
        margin-top: calc(100vw /2.1);
        text-align: center;
    }

    .blackbody {
        background-color: black;
    }

    .whitebody {
        background-color: white;
    }
</style>

<body class="blackbody" id="body">
    <div class="div">
        <button class="whitebutton" onclick="send(value)" id="button" value=01001>OFF</button>
    </div>
</body>
<script>
    var bool = 1;
    function send(a) {
        // 实现，点击后变换颜色
        if (bool == 1) {
            document.getElementById("button").innerText = "ON";
            document.getElementById("button").setAttribute("class","blackbutton");
            //获取HTML元素通过ID，设置元素属性<class 等>
            document.getElementById("body").setAttribute("class","whitebody");
            bool = 2;
        }
        else {
            document.getElementById("button").innerText = "OFF";
            document.getElementById("button").setAttribute("class","whitebutton");
            document.getElementById("body").setAttribute("class","blackbody");
            bool = 1;
        }
    }
</script>

</html>)+*");
}
