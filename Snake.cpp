#include <windows.h>
#include "Snake.h"

#include <array>
#include <memory>
#include <string>
#include <vector>
#include <deque>
#include <set>
#include <utility>

#include <time.h>
#include <conio.h>

static int eat_food = 0;
static int score = 0;
struct Map
{
public:
    Map()
    {
        for (int col = 0; col < MAPHEIGHT; col++)
        {
            for (int row = 0; row < MAPWIDTH; row++)
            {
                if (col == 0 || col == MAPHEIGHT - 1 || row == 0 || row == MAPWIDTH - 1)
                    m_map[col][row] = WALL;
                else
                    m_map[col][row] = AIR;
            }
        }
    }
    void printMap()
    {
        std::string s;
        for (auto &i : m_map)
        {
            for (auto &j : i)
            {
                s += material[j];
            }
            s += '\n';
        }
        puts(s.c_str());
    }
    void update(int x, int y, charPrint value)
    {
        m_map[y][x] = value;
    }
    char getType(int x, int y)
    {
        return m_map[y][x];
    }

private:
    std::array<std::array<int, MAPWIDTH>, MAPHEIGHT> m_map;
};

class Snake
{
private:
    std::deque<std::pair<int, int>> m_snake;
    Map *m_map;
    std::pair<int, int> end = {-1, -1};

public:
    Snake(Map *map) : m_map(map)
    {
        for (int i = 0; i < 3; i++)
        {
            m_snake.push_back(std::make_pair<int, int>(10, 10 - i));
        }
    }
    void update()
    {
        for (auto &pos : m_snake)
        {
            m_map->update(pos.first, pos.second, SNAKE);
        }
        if (end.first != -1)
        {
            m_map->update(end.first, end.second, AIR);
        }
    }
    void move(char direction)
    {
        std::pair<int, int> head = m_snake.front();
        if (direction == 'S')
        {
            head.second++;
        }
        else if (direction == 'W')
        {
            head.second--;
        }
        else if (direction == 'A')
        {
            head.first--;
        }
        else if (direction == 'D')
        {
            head.first++;
        }
        else
        {
            // 不合理的方向
            exit(-1);
        }
        m_snake.push_front(head);
        if (m_map->getType(head.first, head.second) != FOOD)
        {
            end = m_snake.back();
            m_snake.pop_back();
        }
        else
        {
            eat_food = 0;
            end = {-1,-1};
        }
    }
    // 游戏结束返回真
    bool checkStatus()
    {
        bool flag = false;
        std::set<std::pair<int, int>> uniqueElements;
        for (const auto &element : m_snake)
        {
            if (uniqueElements.find(element) != uniqueElements.end())
            {
                flag = true;
            } // 找到元素
            uniqueElements.insert(element);
        }
        if (m_map->getType(m_snake.front().first, m_snake.front().second) == WALL)
            flag = true;
        return flag;
    }
};

class GameManager
{
public:
    GameManager(Map *map) : m_map(map)
    {
        // 初始化地图中的蛇的起始点和终点位置
        m_snake = new Snake(map);
        m_snake->update();
        generateFood();
    }
    bool isOver = false;
    void getkey()
    {
        if (_kbhit())
        {
            key = _getch() & 95;
        }
    }
    void handle()
    {
        if ((key == 'A' && prekey == 'D') || (key == 'S' && prekey == 'W') || (key == 'D' && prekey == 'A') || (key == 'W' && prekey == 'S'))
        {
            key = prekey;
        } // 防止反向移动
        switch (key)
        {
        case 'W':
        case 'A':
        case 'S':
        case 'D':
            m_snake->move(key);
            prekey = key;
            break;
        case 'Q':
            isOver = true;
            return;
            break;
        default:
            m_snake->move(prekey); // 根据前一个方向移动
            break;
        } // 做判断
        isOver = m_snake->checkStatus();
        m_snake->update();

        if(eat_food == 0) generateFood();
    }

private:
    Map *m_map;
    Snake *m_snake;
    int key;
    int prekey = 'S';

    inline void generateFood()
    {
        // 初始化食物位置
        int x = rand() % (MAPWIDTH - 2) + 1;
        int y = rand() % (MAPHEIGHT - 2) + 1;
        m_map->update(x, y, FOOD);
        eat_food = 1;
    }
};

int main()
{
    srand((unsigned)time(0));

    std::unique_ptr<Map> map(new Map);
    std::unique_ptr<GameManager> gm(new GameManager(map.get()));

    do
    {
        system("cls");
        map->printMap();
        gm->getkey();
        gm->handle();

        Sleep(200);
    } while (!gm->isOver);

    printf("\nGame over! You get %d scores.\n", eat_food);
}