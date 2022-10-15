#include "player.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
using namespace std;

void player::try_to_move(int try_way)
{
    switch(try_way)
    {
    case 0:
            pos_y--;
            break;
    case 1:
            pos_y++;
            break;
    case 2:
            pos_x--;
            break;
        case 3:
            pos_x++;
            break;
    }
}
int player::return_pos_x()
{
    return pos_x;
}
int player::return_pos_y()
{
    return pos_y;
}
void player::restore_coords()
{
    pos_x=old_pos_x;
    pos_y=old_pos_y;
}
void player::update_plyer()
{
        const char *buff=" ";
        const char *enem="@";
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord_first = {pos_x,pos_y};
        COORD coord_second = {old_pos_x,old_pos_y};
        SetConsoleCursorPosition(hOutput, coord_second);
        WriteConsoleA(hOutput, buff, 1, NULL,NULL);
        SetConsoleTextAttribute(hOutput, FOREGROUND_INTENSITY | FOREGROUND_GREEN );
        SetConsoleCursorPosition(hOutput, coord_first);
        WriteConsoleA(hOutput, enem, 1, NULL,NULL);
        SetConsoleTextAttribute ( hOutput, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        old_pos_x=pos_x;
        old_pos_y=pos_y;
}
