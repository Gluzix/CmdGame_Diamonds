#include "Map.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
using namespace std;
void Map::create_map()
{
        FILE *plik;
        plik=fopen(path, "r");
        width = width/height;
        fseek(plik, 0, 0);
        for(int i=0; i<height; i++)
        {
            for(int w=0; w<width; w++)
            {
                fscanf(plik, "%c", &start_string[i][w]);
            }
        }
        fclose(plik);
}
void Map::show_map()
{
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            for(int i=0; i<height; i++)
            {
                        for(int w=0; w<width; w++)
                        {
                            if(start_string[i][w]=='*')
                            {
                                points++;
                                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_BLUE);
                                cout<<start_string[i][w];
                                SetConsoleTextAttribute ( h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                            }
                            else if(start_string[i][w]=='$')
                            {
                                cout<<start_string[i][w];
                                barrier_pos_x[counter_of_barriers-1]=w;
                                barrier_pos_y[counter_of_barriers-1]=i;
                                counter_of_barriers++;
                                barrier_pos_x=(int*)realloc(barrier_pos_x,counter_of_barriers*sizeof(int));
                                barrier_pos_y=(int*)realloc(barrier_pos_y,counter_of_barriers*sizeof(int));
                            }
                            else if(start_string[i][w]=='&')
                            {
                                slow_enemy_pos_x[counter_of_slow_enemy_pos-1]=w;
                                slow_enemy_pos_y[counter_of_slow_enemy_pos-1]=i;
                                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY );
                                cout<<start_string[i][w];
                                SetConsoleTextAttribute ( h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                                counter_of_slow_enemy_pos++;
                                slow_enemy_pos_x=(int*)realloc(slow_enemy_pos_x,counter_of_slow_enemy_pos*sizeof(int));
                                slow_enemy_pos_y=(int*)realloc(slow_enemy_pos_y,counter_of_slow_enemy_pos*sizeof(int));
                            }
                            else if(start_string[i][w]=='#')
                            {
                                 SetConsoleTextAttribute(h, FOREGROUND_INTENSITY );
                                 cout<<start_string[i][w];
                                 SetConsoleTextAttribute ( h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                            }
                            else if(start_string[i][w]=='@')
                            {
                                 player_pos_x=w;
                                 player_pos_y=i;
                                 SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_GREEN );
                                 cout<<start_string[i][w];
                                 SetConsoleTextAttribute ( h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                            }
                            else if(start_string[i][w]=='^')
                            {
                                faster_enemy_pos_x[counter_of_faster_enemy_pos-1]=w;
                                faster_enemy_pos_y[counter_of_faster_enemy_pos-1]=i;
                                SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_BLUE );
                                cout<<start_string[i][w];
                                SetConsoleTextAttribute ( h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                                counter_of_faster_enemy_pos++;
                                faster_enemy_pos_x=(int*)realloc(faster_enemy_pos_x,counter_of_faster_enemy_pos*sizeof(int));
                                faster_enemy_pos_y=(int*)realloc(faster_enemy_pos_y,counter_of_faster_enemy_pos*sizeof(int));
                            }
                            else
                            {
                                    cout<<start_string[i][w];
                            }
                        }
            }
}
bool Map::check_if_obstacle_for_slow_enem(int x, int y, int i)
{
    if((start_string[y][x]!='#')&&(start_string[y][x]!='$')&&(start_string[y][x]!='*')&&(start_string[y][x]!='S')&&(start_string[y][x]!='O')&&(start_string[y][x]!='U')&&(start_string[y][x]!='T'))
    {
        slow_enemy_pos_x[i]=x;
        slow_enemy_pos_y[i]=y;
        return true;
    }
    else return false;
}
bool Map::check_if_obstacle_for_fast_enem(int x, int y, int i)
{
    if((start_string[y][x]!='#')&&(start_string[y][x]!='$')&&(start_string[y][x]!='*')&&(start_string[y][x]!='S')&&(start_string[y][x]!='O')&&(start_string[y][x]!='U')&&(start_string[y][x]!='T'))
    {
        faster_enemy_pos_x[i]=x;
        faster_enemy_pos_y[i]=y;
        return true;
    }
    else return false;
}
bool Map::check_if_obstacle_for_player(int x, int y)
{
    if((start_string[y][x]!='#')&&(start_string[y][x]!='$')&&(start_string[y][x]!='S')&&(start_string[y][x]!='O')&&(start_string[y][x]!='U')&&(start_string[y][x]!='T')) return true;
    else return false;
}
int Map::return_player_pos_x()
{
    return player_pos_x;
}
int Map::return_player_pos_y()
{
    return player_pos_y;
}
int Map::return_slow_enem_pos_x(int e)
{
    return slow_enemy_pos_x[e];
}
int Map::return_slow_enem_pos_y(int e)
{
    return slow_enemy_pos_y[e];
}
int Map::return_faster_enem_pos_x(int e)
{
    return faster_enemy_pos_x[e];
}
int Map::return_faster_enem_pos_y(int e)
{
    return faster_enemy_pos_y[e];
}
int Map::return_counter_of_slow_enem_pos()
{
    return counter_of_slow_enemy_pos;
}
int Map::return_counter_of_faster_enem_pos()
{
    return counter_of_faster_enemy_pos;
}
bool Map::check_if_player_lost(int x, int y)
{
    for(int i=0; i<counter_of_faster_enemy_pos; i++)
    {
        if((x==faster_enemy_pos_x[i])&&(y==faster_enemy_pos_y[i])) return true;
    }
    for(int i=0; i<counter_of_slow_enemy_pos; i++)
    {
        if((x==slow_enemy_pos_x[i])&&(y==slow_enemy_pos_y[i])) return true;
    }
    return false;
}
bool Map::check_if_slow_enem_meet_enem(int x, int y, int ii)
{
    for(int i=0; i<counter_of_slow_enemy_pos; i++)
    {
        if((x==faster_enemy_pos_x[i])&&(y==faster_enemy_pos_y[i]))return false;
        else if(i!=ii)
        {
            if((x==slow_enemy_pos_x[i])&&(y==slow_enemy_pos_y[i]))return false;
        }
    }
    return true;
}
bool Map::check_if_faster_enem_meet_enem(int x, int y, int ii)
{
    for(int i=0; i<counter_of_faster_enemy_pos; i++)
    {
        if((x==slow_enemy_pos_x[i])&&(y==slow_enemy_pos_y[i]))return false;
        else if(i!=ii)
        {
            if((x==faster_enemy_pos_x[i])&&(y==faster_enemy_pos_y[i]))return false;
        }
    }
    return true;
}
bool Map::check_if_player_got_diamond(int x, int y)
{
    if(start_string[y][x]=='*')
    {
        start_string[y][x]=' ';
        return true;
    }
    else return false;
}
int Map::return_nmbr_of_required_points()
{
    return points;
}
bool Map::check_if_player_turn_on_switch(int x, int y)
{
    if(start_string[y][x]=='S')
    {
        return true;
    }
    else return false;
}
void Map::delete_barrier()
{
    const char *buff=" ";
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    for(int i=0; i<counter_of_barriers-1; i++)
    {
    start_string[barrier_pos_y[i]][barrier_pos_x[i]]=' ';
    coord = {barrier_pos_x[i], barrier_pos_y[i]};
    SetConsoleCursorPosition(hOutput, coord);
    WriteConsoleA(hOutput, buff, 1, NULL, NULL);
    }
}
bool Map::check_if_player_got_out(int x, int y)
{
    if((start_string[y][x]=='O')||(start_string[y][x]=='U')||(start_string[y][x]=='T'))return true;
    else return false;
}
