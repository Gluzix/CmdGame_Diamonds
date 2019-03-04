#include "faster_enemy.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <time.h>
using namespace std;
void faster_enemy::update_pos()
{
    if(counter!=his_way)
    {
        pos_y--;
        counter++;
    }
    else if(counter_sc==his_way)
    {
        counter=0;
        counter_sc=0;
    }
    else if(counter==his_way)
    {
        pos_y++;
        counter_sc++;
    }
}
void faster_enemy::return_to_old_pos()
{
    pos_y=old_pos_y;
    pos_x=old_pos_x;
}
void faster_enemy::try_update_pos()
{
        const char *buff=" ";
        const char *enem="^";
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord_first = {pos_x,pos_y};
        COORD coord_second = {old_pos_x,old_pos_y};
        SetConsoleCursorPosition(hOutput, coord_second);
        WriteConsoleA(hOutput, buff, 1, NULL,NULL);
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        SetConsoleCursorPosition(hOutput, coord_first);
        WriteConsoleA(hOutput, enem, 1, NULL,NULL);
        SetConsoleTextAttribute ( h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        old_pos_x=pos_x;
        old_pos_y=pos_y;
}
int faster_enemy::return_pos_y()
{
    return pos_y;
}
int faster_enemy::return_pos_x()
{
    return pos_x;
}
