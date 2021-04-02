#pragma onece
int i = 0;
//8*8 屏幕扫描函数
int Sub(int n);
void scan(byte UI[],int sleep=200)
{
    for (i = 0; i < 8; i++)
    {
        //8行，就写八次屏幕了
        for (int j = i; j < i + 8; j++)
        //完成屏幕的输出
        {
            lc.setRow(0, j - i, UI[Sub(j)]);
            //用j-i，来保证row是从0行开始的，而j则是在i的基础上增加，用sub函数
            //来保证大于数组时减去数组长度，使得产生偏移
        }
        delay(100);
    }
}
int Sub(int n)
{
    if (n > 7)
    {
        n = n - 8;
    }
    return n;
}
