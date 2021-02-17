#include "fast_enem.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>

FastEnemy::FastEnemy(int x, int y) :
    m_posX(x),
    m_posY(y),
    m_oldPosX(x),
    m_oldPosY(y),
    m_way(0),
    m_round(0),
    m_disparityX(0),
    m_disparityY(0),
    m_whoUsedRound(0),
    m_xOrY(0),
    m_decision(false) {};

FastEnemy::~FastEnemy()
{

}

void FastEnemy::TryUpdatePos()
{
    if(m_whoUsedRound == 1)
    {
        m_round = 0;
    }
    if(m_round == 2)
    {
        if (m_way == 0)m_posY++;
        else if (m_way == 1) m_posX++;
        else if (m_way == 2) m_posY--;
        else if (m_way == 3) m_posX--;
        m_round =0;
    }
    else m_round ++;
    m_whoUsedRound = 0;
}

void FastEnemy::UpdatePos()
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
void FastEnemy::BackToOldPos()
{
    m_posX = m_oldPosX;
    m_posY = m_oldPosY;
    m_way = rand() % 4;
}
int fast_enem::return_pos_x()
{
    return pos_x;
}
int fast_enem::return_pos_y()
{
    return pos_y;
}
bool fast_enem::check_if_player_is_near(int x, int y)
{
    decision=false;
    disparity_x=pos_x-x;
    disparity_y=pos_y-y;
    if(disparity_x<0)disparity_x=disparity_x*(-1);
    if(disparity_y<0)disparity_y=disparity_y*(-1);
    if((disparity_x<=8)&&(disparity_y<=5))
    {
         if(who_used_round==0)
        {
            round=0;
        }
        decision=true;
        if(round==2)
        {
            if(x_or_y==0)
            {
                round=0;
                if(pos_x>x)
                {
                    pos_x--;
                }
                else if(pos_x<x)
                {
                    pos_x++;
                }
                else if(pos_x==x)
                {
                    if(pos_y>y)
                    {
                        pos_y--;
                    }
                    else if(pos_y<y)
                    {
                        pos_y++;
                    }
                }
                x_or_y=1;
            }
            else if(x_or_y==1)
            {
                round=0;
                if(pos_y>y)
                {
                    pos_y--;
                }
                else if(pos_y<y)
                {
                    pos_y++;
                }
                else if(pos_y==y)
                {
                    if(pos_x>x)
                    {
                        pos_x--;
                    }
                    else if(pos_x<x)
                    {
                        pos_x++;
                    }
                }
                x_or_y=0;
            }
        }
        else round++;
        who_used_round=1;
    }
    return decision;
}
