#include "FastEnemy.h"
#include <windows.h>
#include <string>

const int POS_X = 0;
const int POS_Y = 1;

FastEnemy::FastEnemy(int x, int y) :
    m_posX(x),
    m_posY(y),
    m_oldPosX(x),
    m_oldPosY(y),
    m_way(0),
    m_round(0),
    m_whoUsedRound(0),
    m_coordination(0) {}

FastEnemy::~FastEnemy()
{

}

void FastEnemy::UpdatePosition()
{
    if(m_whoUsedRound == 1)
    {
        m_round = 0;
    }
    if(m_round == 2)
    {
        if (m_way == 0) m_posY++;
        else if (m_way == 1) m_posX++;
        else if (m_way == 2) m_posY--;
        else if (m_way == 3) m_posX--;
        m_round =0;
    }
    else m_round++;
    m_whoUsedRound = 0;
}

void FastEnemy::UpdateConsoleCoordinates()
{
    std::string buffer = " ";
    std::string enemy = "^";
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord_first = { m_posX, m_posY };
    COORD coord_second = { m_oldPosX, m_oldPosY };
    SetConsoleCursorPosition(hOutput, coord_second);
    WriteConsoleA(hOutput, buffer.c_str(), 1, NULL, NULL);
    SetConsoleTextAttribute(hOutput, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    SetConsoleCursorPosition(hOutput, coord_first);
    WriteConsoleA(hOutput, enemy.c_str(), 1, NULL, NULL);
    SetConsoleTextAttribute (hOutput, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    m_oldPosX = m_posX;
    m_oldPosY = m_posY;
}

void FastEnemy::BackToOldPosition()
{
    m_posX = m_oldPosX;
    m_posY = m_oldPosY;
    m_way = rand() % 4;
}

bool FastEnemy::IsPlayerNear(int x, int y)
{
    bool decision = false;
    int disparityX = m_posX - x;
    int disparityY = m_posY - y;
    if (disparityX < 0) disparityX = disparityX * (-1);
    if (disparityY < 0) disparityY = disparityY * (-1);
    if ((disparityX <= 8) && (disparityY <= 5))
    {
        if (m_whoUsedRound == 0)
        {
            m_round = 0;
        }
        decision = true;
        if (m_round == 2)
        {
            if (m_coordination == POS_X)
            {
                m_round = 0;
                if (m_posX > x)
                {
                    m_posX--;
                }
                else if (m_posX < x)
                {
                    m_posX++;
                }
                else if (m_posX == x)
                {
                    if (m_posY > y)
                    {
                        m_posY--;
                    }
                    else if (m_posY < y)
                    {
                        m_posY++;
                    }
                }
                m_coordination = POS_Y;
            }
            else if (m_coordination == POS_Y)
            {
                m_round = 0;
                if (m_posY > y)
                {
                    m_posY--;
                }
                else if (m_posY < y)
                {
                    m_posY++;
                }
                else if (m_posY == y)
                {
                    if (m_posX > x)
                    {
                        m_posX--;
                    }
                    else if (m_posX < x)
                    {
                        m_posX++;
                    }
                }
                m_coordination = POS_X;
            }
        }
        else m_round++;
        m_whoUsedRound = 1;
    }
    return decision;
}

int FastEnemy::GetX()
{
    return m_posX;
}

int FastEnemy::GetY()
{
    return m_posY;
}
