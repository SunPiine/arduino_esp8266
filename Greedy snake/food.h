#pragma once
#include "Arduino.h"
#include "map.h"
/*包含食物的方法：产生、食物的当前位置
食物的消失在snake 类内部方法内部实现
*/
class food
{
private:
    body food_local;

public:
    food()
    {
        // food_local.x = 5;
        // food_local.y = 0; //测试代码，不控制的条件下eat
        food_local.x = 2;
        food_local.y = 2;
    };
    body &read_food()
    {
        return food_local;
    }
    body &new_food()
    {
        food_local.x = random(0, 8);
        food_local.y = random(0, 8);
        return food_local;
    }
};
