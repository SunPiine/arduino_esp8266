#include <LedControl.h>
auto din = D5;
auto cs = D6;
auto clk = D7;
LedControl lc(din, clk, cs, 4);
void printByte(byte character[]);
int sub(int n);
byte eight[8] = {0x7E, 0x7E, 0x66, 0x7E, 0x7E, 0x66, 0x7E, 0x7E}; //8
byte UI[8] = {0x15, 0xEE, 0xA4, 0x5F, 0xA4, 0x5F, 0xA4, 0x04};
void setup()
{
    lc.shutdown(0, false);
    lc.setIntensity(0, 3);
    lc.clearDisplay(0);
}
void loop()
{
    lc.clearDisplay(0);
    lc.setIntensity(0, 2);
    int i = 0;
    for (i = 0; i < 8; i++)
    {
        //8行，就写八次屏幕了
        for (int j = i; j < i + 8; j++)
        //完成屏幕的输出
        {
            lc.setRow(0, j - i, UI[sub(j)]);
            //用j-i，来保证row是从0行开始的，而j则是在i的基础上增加，用sub函数
            //来保证大于数组时减去数组长度，使得产生偏移
        }
        delay(300);
    }
}

int sub(int n)
{
    if (n > 7)
    {
        n = n - 8;
    }
    return n;
}