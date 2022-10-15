#include "FastestEnemy.h"
#include <windows.h>
#include <string>

FastestEnemy::FastestEnemy(int x, int y, int hisway):
    m_posY(y), 
    m_oldPosY(y),
    m_posX(x),
    m_oldPosX(x),
    m_hisWay(hisway),
    m_counter(0),
    m_counterSecond(0){}

void FastestEnemy::UpdatePosition()
{
    if (m_counter != m_hisWay)
    {
        m_posY--;
        m_counter++;
    }
    else if (m_counterSecond == m_hisWay)
    {
        m_counter = 0;
        m_counterSecond = 0;
    }
    else if (m_counter == m_hisWay)
    {
        m_posY++;
        m_counterSecond++;
    }
}

void FastestEnemy::UpdateConsoleCoordinates()
{
    std::string buffer = " ";
    std::string enemy = "^";
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord_first = { m_posX, m_posY };
    COORD coord_second = { m_oldPosX, m_oldPosY };
    SetConsoleCursorPosition(hOutput, coord_second);
    WriteConsoleA(hOutput, buffer.c_str(), 1, NULL, NULL);
    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
    SetConsoleCursorPosition(hOutput, coord_first);
    WriteConsoleA(hOutput, enemy.c_str(), 1, NULL, NULL);
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    m_oldPosX = m_oldPosX;
    m_oldPosY = m_oldPosY;
}

void FastestEnemy::BackToOldPosition()
{
    m_posY = m_oldPosY;
    m_posX = m_oldPosX;
}

int FastestEnemy::GetX()
{
    return m_oldPosY;
}

int FastestEnemy::GetY()
{
    return m_oldPosX;
}
