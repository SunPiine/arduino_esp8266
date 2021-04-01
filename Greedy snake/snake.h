#pragma once
#include <Arduino.h>
#include "food.h"
#include "map.h"
/*debug 日记,误将inint() 写成init(),导致不断重启,已经改为inint_map(),功能正常*/
/* snake 类包含了，贪吃蛇的方法：移动、进食、死亡、方向改变、获得食物、胜利、死亡
和对应的数据，但是还有一个Bug 即有时会莫名的胜利/重启，在吃了food 后，可能是
胜利条件的判断有误，或者是have_food() 有问题:|，不管如何我没能排查出来:{ */
/*是否进食的逻辑本文件未实现，外部文件可以这样使用
 if (snakes.snake_head_local() == snakes.read_food())
    {
        snakes.eat();
    }
*/
//头前进，尾巴消失的方法进行移动的模拟，吃了后尾巴变长再移动
const bool mode = true;
//是否存在蛇蛇
class snake : public map, public food
{
private:
    char snakelong;
    unsigned char trend = 0;  //用control 修改trend，方向修改问题放在control 里处理
                              //trend 指导move ，两相隔离
    unsigned char runing = 0; //当前是咋跑的
    body *snake_body;
    bool live = true;
    bool wined = false;

public:
    snake() = default;
    snake(char sl = 3, char w = 8, char h = 8) : snakelong(sl), map(w, h), food()
    {
        snake_body = new body[snakelong];
        for (char i = 0; i < sl; i++)
        {
            snake_body[i].y = i + 3;
            snake_body[i].x = 5;
        }
        for (unsigned char i = 0; i < snakelong; i++)
        {
            writ(snake_body[i].x, snake_body[i].y, mode);
        }
        writ(read_food().x, read_food().y, mode);
    }
    ~snake()
    {
        delete[] snake_body;
    }
    void contorl(char);
    void eat();
    body &snake_head_local();
    void move();
    void dead();
    bool health();
    void have_food();
    void win();
    bool read_wined();
};
void snake::eat()
//是否吃到食物由外部控制，本函数只控制吃这一行为
{
    snakelong++;
    map_sturct smpst = return_map_sturct();
    auto new_snake_body = new body[snakelong];
    for (char i = 0; i < snakelong - 1; i++)
    {
        new_snake_body[i] = snake_body[i];
    }
    delete[] snake_body;
    if (new_snake_body[snakelong - 2].x == new_snake_body[snakelong - 3].x)
    {
        new_snake_body[snakelong-1].x = new_snake_body[snakelong - 2].x;
        if (new_snake_body[snakelong - 2].y < new_snake_body[snakelong - 3].y)
        //竖着向下
        {
            new_snake_body[snakelong-1].y = new_snake_body[snakelong - 2].y - 1;
        }
        else
        {
            new_snake_body[snakelong-1].y = new_snake_body[snakelong - 2].y + 1;
        }
        if (new_snake_body[snakelong-1].y < 0)
        {
            new_snake_body[snakelong-1].y = smpst.height - 1;
        }
        else if (new_snake_body[snakelong-1].y > smpst.height - 1)
        {
            new_snake_body[snakelong-1].y = 0;
        }
    }
    else if (new_snake_body[snakelong - 2].y == new_snake_body[snakelong - 3].y)
    {
        new_snake_body[snakelong-1].x = new_snake_body[snakelong - 2].x;
        if (new_snake_body[snakelong - 2].x < new_snake_body[snakelong - 3].x)
        //横着向右
        {
            new_snake_body[snakelong-1].x = new_snake_body[snakelong - 2].x - 1;
        }
        else
        {
            new_snake_body[snakelong-1].x = new_snake_body[snakelong - 2].x + 1;
        }
        if (new_snake_body[snakelong-1].x < 0)
        {
            new_snake_body[snakelong-1].x = smpst.widght - 1;
        }
        else if (new_snake_body[snakelong-1].x > smpst.widght - 1)
        {
            new_snake_body[snakelong-1].x = 0;
        }
    }
    snake_body = new_snake_body;
    inint_map();
    for (unsigned char i = 0; i < snakelong; i++)
    {
        writ(snake_body[i].x, snake_body[i].y, mode);
    }
    have_food();
    if (snake_body[snakelong-1] == snake_head_local())
    {
        dead();
    }
    writ(read_food().x, read_food().y, mode);
}
void snake::move()
{
    map_sturct smpst;
    smpst = return_map_sturct();
    switch (trend)
    {
    case 0:
        //up
        for (char i = snakelong; i > 0; i--)
        {
            snake_body[i] = snake_body[i - 1];
        }
        snake_body[0].x = snake_body[1].x;
        snake_body[0].y = (snake_body[0].y - 1) < 0 ? smpst.height - 1 : (snake_body[0].y - 1);
        runing = 0;
        break;
    case 1:
        //down
        for (char i = snakelong; i > 0; i--)
        {
            snake_body[i] = snake_body[i - 1];
        }
        snake_body[0].x = snake_body[1].x;
        snake_body[0].y = (snake_body[0].y + 1) > smpst.height - 1 ? 0 : (snake_body[0].y + 1);
        runing = 1;
        break;
    case 2:
        //lift
        for (char i = snakelong; i > 0; i--)
        {
            snake_body[i] = snake_body[i - 1];
        }
        snake_body[0].y = snake_body[1].y;
        snake_body[0].x = (snake_body[0].x - 1) < 0 ? smpst.widght - 1 : (snake_body[0].x - 1);
        runing = 2;
        break;
    case 3:
        // right
        for (char i = snakelong; i > 0; i--)
        {
            snake_body[i] = snake_body[i - 1];
        }
        snake_body[0].y = snake_body[1].y;
        snake_body[0].x = (snake_body[0].x + 1) > smpst.widght - 1 ? 0 : (snake_body[0].x + 1);
        runing = 3;
        break;
    default:
        break;
    };
    inint_map();
    for (unsigned char i = 0; i < snakelong; i++)
    {
        writ(snake_body[i].x, snake_body[i].y, mode);
    }
    writ(read_food().x, read_food().y, mode);
    //死了没？,身体和头的重合判断，上面已经完成了坐标移动，故重合即去世
    bool test = false;
    for (unsigned char i = 1; i < snakelong; i++) //从1开始，0是头，头肯定和头重合的:>
    {
        test = test || (snake_head_local() == snake_body[i]);
    }
    if (test)
    {
        dead();
    }
}
body &snake::snake_head_local()
//返回引用，可以在其后直接用‘.’使用x，y位置
{
    return snake_body[0];
}
void snake::dead()
{
    live = false;
}
bool snake::health()
{
    return live;
}
void snake::contorl(char ct)
//control 不可改变runing ，runing由move 维护。
{
    if (ct == runing)
    {
        return;
    }
    switch (ct)
    {
    case 0:
        if (runing == 1)
        {
            break;
        }
        trend = 0;
        break;
    case 1:
        if (runing == 0)
        {
            break;
        }
        trend = 1;
        break;
    case 2:
        if (runing == 3)
        {
            break;
        }
        trend = 2;
        break;
    case 3:
        if (runing == 2)
        {
            break;
        }
        trend = 3;
        break;
    default:
        break;
    }
    return;
}
void snake::have_food()
{
    if (snakelong == (return_map_sturct().widght * return_map_sturct().height - 1))
    {
        win();
        return;
    }
    body b = new_food();
    bool test = false;
    while (true)
    {
        for (unsigned char i = 0; i < snakelong; i++)
        {
            test = test || (snake_body[i] == b);
        }
        if (!test)
        {
            return;
        }
        b = new_food();
        test=false;
    }
}
void snake::win()
{
    wined = true;
}
bool snake::read_wined()
{
    return wined;
}
