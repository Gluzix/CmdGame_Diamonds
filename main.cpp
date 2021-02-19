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

                //for (int i = 0; i < 14; i++)
                //{
                //    container.push_back(SlowEnemy(mp1.return_slow_enem_pos_x(i), mp1.return_slow_enem_pos_y(i)));
                //}

                for (int i = 0; i < 5; i++)
                {
                    container.push_back(new FastEnemy(mp1.return_faster_enem_pos_x(i), mp1.return_faster_enem_pos_y(i)));
                }

                while(1)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        ((FastEnemy*)container[i])->UpdatePosition();
                        while (!mp1.check_if_obstacle_for_fast_enem(((FastEnemy*)container[i])->GetX(), ((FastEnemy*)container[i])->GetY(), i) ||
                            !mp1.check_if_faster_enem_meet_enem(((FastEnemy*)container[i])->GetX(), ((FastEnemy*)container[i])->GetY(), i))
                        {
                            ((FastEnemy*)container[i])->BackToOldPosition();
                            ((FastEnemy*)container[i])->UpdatePosition();
                        }
                        ((FastEnemy*)container[i])->UpdateConsoleCoordinates();
                    }
                    Sleep(3);
                    //Sleep(1);
                    //for (int i = 14; i < 20; i++)
                    //{
                    //    container[i].UpdatePosition();
                    //    while (!mp1.check_if_obstacle_for_fast_enem(container[i].GetX(), container[i].GetY(), i) ||
                    //        !mp1.check_if_faster_enem_meet_enem(container[i].GetX(), container[i].GetY(), i))
                    //    {
                    //        container[i].BackToOldPosition();
                    //        container[i].UpdatePosition();
                    //    }
                    //    container[i].UpdateConsoleCoordinates();
                    //}
                    //Sleep(1);
                    //for (int i = 14; i < 20; i++)
                    //{
                    //    container[i].UpdatePosition();
                    //    while (!mp1.check_if_obstacle_for_fast_enem(container[i].GetX(), container[i].GetY(), i) ||
                    //        !mp1.check_if_faster_enem_meet_enem(container[i].GetX(), container[i].GetY(), i))
                    //    {
                    //        container[i].BackToOldPosition();
                    //        container[i].UpdatePosition();
                    //    }
                    //    container[i].UpdateConsoleCoordinates();
                    //}
                    //Sleep(1);
                    //for (int i = 0; i < 14; i++)
                    //{
                    //    container[i].UpdatePosition();
                    //    while (!mp1.check_if_obstacle_for_slow_enem(container[i].GetX(), container[i].GetY(), i) ||
                    //        !mp1.check_if_slow_enem_meet_enem(container[i].GetX(), container[i].GetY(), i))
                    //    {
                    //        container[i].BackToOldPosition();
                    //        container[i].UpdatePosition();
                    //    }
                    //    container[i].UpdateConsoleCoordinates();
                    //}
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
