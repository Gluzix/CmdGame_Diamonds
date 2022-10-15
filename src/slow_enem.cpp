#include "slow_enem.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
using namespace std;
void slow_enem::try_update_pos()
{
    if(who_used_round==1)
    {
        round=0;
    }
    if(round==4)
    {
        if(way==0)pos_y++;
        else if(way==1)pos_x++;
        else if(way==2)pos_y--;
        else if(way==3)pos_x--;
        round=0;
    }
    else round++;
    who_used_round=0;
}
void slow_enem::update_pos()
{
    const char *buff=" ";
    const char *enem="&";
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord_first = {pos_x, pos_y};
    COORD coord_second = {old_pos_x, old_pos_y};
    SetConsoleCursorPosition(hOutput, coord_second);
    WriteConsoleA(hOutput, buff, 1, NULL, NULL);
    SetConsoleTextAttribute(hOutput, FOREGROUND_RED | FOREGROUND_INTENSITY);
    SetConsoleCursorPosition(hOutput, coord_first);
    WriteConsoleA(hOutput, enem, 1, NULL, NULL);
    SetConsoleTextAttribute (hOutput, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    old_pos_x=pos_x;
    old_pos_y=pos_y;
}
void slow_enem::return_to_old_pos()
{
    pos_x=old_pos_x;
    pos_y=old_pos_y;
    way=rand() % 4;
}
int slow_enem::return_pos_x()
{
    return pos_x;
}
int slow_enem::return_pos_y()
{
    return pos_y;
}
//Funkcje autonamierzania trzeba zrobic, zeby gra byla bardziej rozbudowana oraz trudniejsza
bool slow_enem::check_if_player_is_near(int x, int y)
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
        if(round==4)
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

