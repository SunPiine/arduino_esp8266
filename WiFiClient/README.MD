# 综合ESP8266 HTML和CSS的项目 
1. 包含文件WIFIClient.ino;WiFiLink_class.h;和ON+OFF.html
2. html 文件使用css html5 和Javascript语言编写，实现了一个圆形按钮和背景色变化，从而控制和显示灯的状态
3. 效果的实现基于Javascript的DOM和事件处理，具体通过对属性节点的捕获和修改元素属性的值实行效果
4. 截止目前还未与HTML具体连接通信21-03-09
5. 参考书目《Web前端开发技术》章慧，南京大学出版社
6. 已经可以实现客户端和网页通讯21-03-11 
7. 程序实现控制ESP-8266F 的板载LED wifi网络开关控制  
8. HTML 通过<a></a> 标签以更换网址方式通讯  
9. <a href=yourURLString > 我把按钮实现放在此处 <a>
10. URLString 一般为 ./Webstute?variate=value 
11. Webstute 在客户端被server.on() 方法捕捉（以Sting） ，value被server.arg(aritate) 方法返回
