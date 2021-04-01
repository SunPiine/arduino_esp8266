#include "snake.h"
#include <LedControl.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
auto din = D1;
auto cs = D2;
auto clk = D3;
auto RI = D5;
IRrecv myIR(RI);        //红外模块，用来控制蛇蛇的方向，因为我的按钮还没到:<
decode_results results; //转换红外数据
byte win_code[] = {0x00, 0x7E, 0x42, 0x7A, 0x40, 0x3E, 0x08, 0x00};
byte dead_code[] = {0x00, 0x18, 0x24, 0x42, 0x5A, 0x24, 0x18, 0x42};
LedControl lc(din, clk, cs, 4);
snake snakes(3, 8, 8);
void show();
void setup()
{
    myIR.enableIRIn(RI);
    lc.shutdown(0, false);
    lc.setIntensity(0, 1);
    lc.clearDisplay(0);
    for (char i = 0; i < 8; i++)
    {
        lc.setRow(0, i, win_code[i]);
    }
    delay(700);
    lc.clearDisplay(0);
    show();
}

void loop()
{
    delay(150);
    show();
    snakes.move();
    if (snakes.snake_head_local() == snakes.read_food())
    {
        snakes.eat();
    }
    if (snakes.read_wined())
    {
        for (char i = 0; i < 8; i++)
        {
            lc.setRow(0, i, win_code[i]);
        }
        Serial.println("wined");
        delay(500);
        exit(0);
    }
    if (!snakes.health())
    {
        for (char i = 0; i < 8; i++)
        {
            lc.setRow(0, i, dead_code[i]);
        }
        Serial.println("dead");
        delay(500);
        exit(0);
    }
    RI_control();
}
void show() //已经验证此函数没有问题，snake 数据结构没有问题
{
    lc.clearDisplay(0);
    delay(1);
    for (char i = 0; i < 8; i++)
    {
        for (char j = 0; j < 8; j++)
        {
            lc.setLed(0, i, j, snakes.show()[i * snakes.return_map_sturct().widght + j]);
        }
    }
    return;
}
void RI_control()
{
    if (myIR.decode(&results))
    {
        myIR.resume();
        if (results.value == 0xFF18E7)
        {
            snakes.contorl(0);
        }
        if (results.value == 0xFF4AB5)
        {
            snakes.contorl(1);
        }
        if (results.value == 0xFF10EF)
        {
            snakes.contorl(2);
        }
        if (results.value == 0xFF5AA5)
        {
            snakes.contorl(3);
        }
        if (results.value == 0xFF38C7)
        {
            snakes.dead();
        }
    }
    return;
}
