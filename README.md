# arduino_esp8266
>学习arduino_esp8266过程中自己总结的相关代码和及经验。
# 1.前置配置
使用 vscode 和arduino IDE 配合编程；

## Arduino 配置
[esp8266 SDK 安装方法](https://www.arduino.cn/thread-76029-1-1.html)

## vscode 配置
在vscode 中搜索 Arduino 安装；
正确配置 Arduino path；
需要安装C/C++扩展；
另外如果使用的是GCC编译器或其它，需要修改.vscode ->c_cpp_properties->intelliSenseMode

## vscode 中的问题
1.输出乱码（关于中文） ：
> 找到 C:\User\YourName\.vscode\extensions\vsciot-vscode.vscode-arduino-0.2.29\out\src\common\util.js
> 找到215 行，关于os.platform 的 if 语句块 ，整个注释掉。
> 文件地址和自己的电脑用户名还有arduino 版本号有关

2.编辑 ino 文件过程中大量报错，包括头文件等：
> 在设置中搜索设置 intelli Sense Engine 更改为 Tag parser 
> 需要注意的是，这一操作也使得cpp 一般错误提示关闭了

# 2.开始 vscode+ Arduino 编程
## Arduino 库
使用Arduino 自带的库管理器安装，并且参考例子
## 开始 vscode 
1.建议在Arduino IDE中完成新建文件和库头文件的引入，保存在合适位置再用　vscode 打开文件夹，再打开ino文件 vscode 会自动完成arduino配置，在vscode 的右下方有关于波特率和板子型号的选择；
2.在Arduino IDE中完成新建文件时会自动新建相应名字的文件夹。  

# 3. 我的开发板  
1. 开发板的型号时ESP8266-12F
2. 选择 

|项目|配置|
| ------- | ------- |
|Baord|NodeMCU 1.0|
|Flash Size|4MB FS:3MB OTA:~512KB|  

#4.更新日志

1.21-03-09：创建WifiClient 项目，提交了相关文件。   
2.21-03-09：修改WiFiLink_class.h 添加了get_input() 方法，修改了linking() 方法；创建class_h自定义文件夹，并上传文件。 
 
>1.get_input(String &str1,String &str2) 方法，从串口读取字符串wifiname 和 wifipassword 
>
>2.修改linking() 方法，使用get_input() 方法，在连接完成前在串口输入任意字符串，即可让8266开始从串口读取新的wifi 登录信息，包括提示。
>
>3.class_h自定义文件夹，将包含我在项目中所有进行包装的方法和对象，反便以后使用，与项目一同更新。   

3.21-03-10: 完成ESP8266与网页的交互，提交更新了文件。 

>1.使用server.arg() 方法和 server.on()、server.send() 方法完成了信息交互过程
>
>2.在html 中使用 ```<a> <a>```
>
> 3.具体见![image](https://user-images.githubusercontent.com/75567322/110815059-09d42b80-82c5-11eb-9c9b-3cc605b84c8b.png)

