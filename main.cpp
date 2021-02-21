#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <windowsx.h>
#include <conio.h>
#include <time.h>
#include <vector>
#include "Menu.h"
#include "Map.h"
#include "Player.h"
#include "FastEnemy.h"
#include "SlowEnemy.h"

using namespace std;


int check_height(const char *str)
{
    int i,w,width,height;
    char buforek;
    width=1;
    height=1;
    FILE *plik;
    plik=fopen(str, "r");
    if (plik == NULL)
    {
        cout<<"Error";
    }
    else
    {
        while(fscanf_s(plik, "%c", &buforek)!=EOF)
        {
            width++;
            if(buforek=='\n')
            {
                height++;
            }
        }
    }
    fclose(plik);
    return height;
}

int check_width(const char *str)
{
    int i,w,width,height;
    char buforek;
    width=1;
    height=1;
    FILE *plik;
    plik=fopen(str, "r");
    if (plik == NULL)
    {
        cout<<"Error";
    }
    else
    {
        while(fscanf_s(plik, "%c", &buforek)!=EOF)
        {
            width++;
            if(buforek=='\n')
            {
                height++;
            }
        }
    }
    fclose(plik);
    return width;
}

int main()
{
    srand( time( NULL ) );
    int x=0;
    Menu m1(check_width("resources/Start.txt"), check_height("resources/Start.txt"), "resources/Start.txt");
    m1.create_menu();
    Map mp1(check_width("resources/Map.txt"), check_height("resources/Map.txt"), "resources/Map.txt");
    mp1.create_map();
    int way = 0;

    while(1)
    {
        while(1)
        {
            m1.show_menu(x);
            if(GetAsyncKeyState(VK_UP))
            {
                if(x>0) x--;
                else x=2;
            }
            else if(GetAsyncKeyState(VK_DOWN))
            {
                if(x<2) x++;
                else x=0;
            }
            else if(GetAsyncKeyState(VK_RETURN))
            {
                system("cls");
                break;
            }
            _getch();
               system("cls");
        }
            if(x==0)
            {
                mp1.show_map();

                std::vector<Enemy*> container;
                player player(mp1.return_player_pos_x(), mp1.return_player_pos_y());

                for (int i = 0; i < 13; i++)
                {
                    container.push_back(new SlowEnemy(mp1.return_slow_enem_pos_x(i), mp1.return_slow_enem_pos_y(i)));
                }

                for (int i = 0; i < 5; i++)
                {
                    container.push_back(new FastEnemy(mp1.return_faster_enem_pos_x(i), mp1.return_faster_enem_pos_y(i)));
                }

                while(1)
                {
                    if (GetAsyncKeyState(VK_UP))
                    {
                        way = 0;
                    }
                    else if (GetAsyncKeyState(VK_DOWN))
                    {
                        way = 1;
                    }
                    else if (GetAsyncKeyState(VK_LEFT))
                    {
                        way = 2;
                    }
                    else if (GetAsyncKeyState(VK_RIGHT))
                    {
                        way = 3;
                    }

                    player.try_to_move(way);
                    if (!mp1.check_if_obstacle_for_player(player.return_pos_x(), player.return_pos_y()))
                    {
                        player.restore_coords();
                    }
                    player.update_plyer();
                    way = -1;

                    for (int i = 13; i < 17; i++)
                    {   
                        if (!((FastEnemy*)container[i]->IsPlayerNear(player.return_pos_x(), player.return_pos_y())))
                        {
                            ((FastEnemy*)container[i])->UpdatePosition();
                        }
                       
                        while (!mp1.check_if_obstacle_for_fast_enem(((FastEnemy*)container[i])->GetX(), ((FastEnemy*)container[i])->GetY(), i) ||
                            !mp1.check_if_faster_enem_meet_enem(((FastEnemy*)container[i])->GetX(), ((FastEnemy*)container[i])->GetY(), i))
                        {
                            ((FastEnemy*)container[i])->BackToOldPosition();
                            if (!((FastEnemy*)container[i]->IsPlayerNear(player.return_pos_x(), player.return_pos_y())))
                            {
                                ((FastEnemy*)container[i])->UpdatePosition();
                            }
                        }     
                        ((FastEnemy*)container[i])->UpdateConsoleCoordinates();
                    }
                    Sleep(100);

                    if (GetAsyncKeyState(VK_UP))
                    {
                        way = 0;
                    }
                    else if (GetAsyncKeyState(VK_DOWN))
                    {
                        way = 1;
                    }
                    else if (GetAsyncKeyState(VK_LEFT))
                    {
                        way = 2;
                    }
                    else if (GetAsyncKeyState(VK_RIGHT))
                    {
                        way = 3;
                    }

                    player.try_to_move(way);
                    if (!mp1.check_if_obstacle_for_player(player.return_pos_x(), player.return_pos_y()))
                    {
                        player.restore_coords();
                    }
                    player.update_plyer();
                    way = -1;

                    for (int i = 13; i < 17; i++)
                    {
                        if (!((FastEnemy*)container[i]->IsPlayerNear(player.return_pos_x(), player.return_pos_y())))
                        {
                            ((FastEnemy*)container[i])->UpdatePosition();
                        }

                        while (!mp1.check_if_obstacle_for_fast_enem(((FastEnemy*)container[i])->GetX(), ((FastEnemy*)container[i])->GetY(), i) ||
                            !mp1.check_if_faster_enem_meet_enem(((FastEnemy*)container[i])->GetX(), ((FastEnemy*)container[i])->GetY(), i))
                        {
                            ((FastEnemy*)container[i])->BackToOldPosition();
                            if (!((FastEnemy*)container[i]->IsPlayerNear(player.return_pos_x(), player.return_pos_y())))
                            {
                                ((FastEnemy*)container[i])->UpdatePosition();
                            }
                        }
                        ((FastEnemy*)container[i])->UpdateConsoleCoordinates();
                    }
                    Sleep(100);

                    if (GetAsyncKeyState(VK_UP))
                    {
                        way = 0;
                    }
                    else if (GetAsyncKeyState(VK_DOWN))
                    {
                        way = 1;
                    }
                    else if (GetAsyncKeyState(VK_LEFT))
                    {
                        way = 2;
                    }
                    else if (GetAsyncKeyState(VK_RIGHT))
                    {
                        way = 3;
                    }

                    player.try_to_move(way);
                    if (!mp1.check_if_obstacle_for_player(player.return_pos_x(), player.return_pos_y()))
                    {
                        player.restore_coords();
                    }
                    player.update_plyer();
                    way = -1;

                    for (int i = 0; i < 13; i++)
                    {
                        if (!((SlowEnemy*)container[i]->IsPlayerNear(player.return_pos_x(), player.return_pos_y())))
                        {
                            ((SlowEnemy*)container[i])->UpdatePosition();
                        }

                        while (!mp1.check_if_obstacle_for_slow_enem(((SlowEnemy*)container[i])->GetX(), ((SlowEnemy*)container[i])->GetY(), i) ||
                            !mp1.check_if_slow_enem_meet_enem(((SlowEnemy*)container[i])->GetX(), ((SlowEnemy*)container[i])->GetY(), i))
                        {
                            ((SlowEnemy*)container[i])->BackToOldPosition();
                            if (!((SlowEnemy*)container[i]->IsPlayerNear(player.return_pos_x(), player.return_pos_y())))
                            {
                                ((SlowEnemy*)container[i])->UpdatePosition();
                            }
                        }
                        ((SlowEnemy*)container[i])->UpdateConsoleCoordinates();

                    }
                }
            }
            else if(x==1)
            {
                system("cls");
                cout<<"About creators:";
                break;//something to do
            }
                else if(x==2) exit(0);//something to do
    }
    return 0;
}
