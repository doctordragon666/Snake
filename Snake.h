#ifndef SNAKE_H
#define SNAKE_H

#define MAPWIDTH 35//宽度
#define MAPHEIGHT 15//高度

char material[4] = {'0', 'D', 'Y', ' '};
enum charPrint
{
    WALL = 0,
    SNAKE,
    FOOD,
    AIR
};

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

#endif