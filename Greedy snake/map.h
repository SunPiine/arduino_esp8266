#pragma once
#include <Arduino.h>
//存放着地图相关的数据结构和方法，即屏幕点；在snake 类中委托构造
struct map_sturct
{
    char height, widght;
    map_sturct &operator=(map_sturct m)
    {
        height = m.height;
        widght = m.widght;
        return *this;
    }
};
struct body
{
    char x;
    char y;
    body &operator=(body b)
    {
        x = b.x;
        y = b.y;
        return *this;
    }
    bool operator==(body b)
    {
        if ((b.x == x) && (b.y == y))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
class map
{
private:
    const char height, width;
    byte *mapdata;
    map_sturct mpst;

public:
    map() = default;
    map(char h = 8, char w = 8) : height(h), width(w)
    {
        mapdata = new byte[height * width];
        //一维数组保命:<
        mpst.height = height;
        mpst.widght = width;
        inint_map();
    }
    ~map()
    {
        delete[] mapdata;
    }
    void writ(char, char, bool);
    byte* show();
    map_sturct return_map_sturct();
    void inint_map();
};
void map::inint_map()
{
    for (unsigned char i = 0; i < width * height; i++)
    {
        mapdata[i] = false;
    }
}
void map::writ(char x, char y, bool d)
//单行向二维转换，h*W+w=D,(w,h),(x,y),D=y*X+x
{
    mapdata[y * width + x] = d;
}
map_sturct map::return_map_sturct()
{
    return mpst;
}
byte* map::show()
{
    return mapdata;
}