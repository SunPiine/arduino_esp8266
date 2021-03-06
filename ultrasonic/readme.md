# 基本介绍 

1. ultrasonic 项目是基于硬件HC-SR04 超声模块和DS18B20 测温模块  
2. DS18B20 模块提供温度用来修正声速，虽然没什么用  
3. 对使用到的函数进行了封装，分别归属temp_class.h 和ultrasonic_class.h  
4. 头文件内有使用说明  
5. 使用temp_class.h 需要注意的是，本类基于
     1. OneWire.h 需要在Arduino IDE 库管理器中安装支持库
     2. 只针对单一DS18B20 设备，需要更高级和更多设备控制，可以在Arduino IDE 库管理器安装对应库  
6. 类的构造函数对引脚进行绑定，切记进行初始化，避免默认构造函数
