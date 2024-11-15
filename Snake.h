#ifndef SNAKE_H
#define SNAKE_H

#define SNAKESIZE 100//蛇的身体最大节数
#define MAPWIDTH 35//宽度
#define MAPHEIGHT 15//高度

#define W 15
#define H W
#define S (W * H)



char material[4] = {'0', 'D', 'Y', ' '};
enum charPrint
{
    WALL = 0,
    SNAKE,
    FOOD,
    AIR
};

#endif