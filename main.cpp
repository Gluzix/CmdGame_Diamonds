#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <windowsx.h>
#include <conio.h>
#include "Menu.h"
#include "Map.h"
#include "enemy.h"
#include "player.h"
#include <time.h>
#include "faster_enemy.h"

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
        while(fscanf(plik, "%c", &buforek)!=EOF)
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
        while(fscanf(plik, "%c", &buforek)!=EOF)
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
    Menu m1(check_width("Start.txt"), check_height("Start.txt"), "Start.txt");
    m1.create_menu();
    Map mp1(check_width("Level_one/Map.txt"), check_height("Level_one/Map.txt"), "Level_one/Map.txt");
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
                enemy e1(mp1.return_pos_x(0), mp1.return_pos_y(0), 3, 0, 8);
                enemy e2(mp1.return_pos_x(1), mp1.return_pos_y(1), 4, 0, 4);
                enemy e3(mp1.return_pos_x(2), mp1.return_pos_y(2), 5, 0, 8);
                enemy e4(mp1.return_pos_x(3), mp1.return_pos_y(3), 6, 0, 4);

                enemy e5(mp1.return_pos_x(4), mp1.return_pos_y(4), -50, 1, 8);
                enemy e6(mp1.return_pos_x(5), mp1.return_pos_y(5), 15, 0, 9);
                enemy e7(mp1.return_pos_x(6), mp1.return_pos_y(6), -48, 1, 8);
                enemy e8(mp1.return_pos_x(7), mp1.return_pos_y(7), 17, 0, 9);
                enemy e9(mp1.return_pos_x(8), mp1.return_pos_y(8), 19, 0, 9);

                faster_enemy fe1(mp1.return_faster_pos_x(0), mp1.return_faster_pos_y(0), 12, 0, 11);
                faster_enemy fe2(mp1.return_faster_pos_x(1), mp1.return_faster_pos_y(1), 12, 0, 11);
                faster_enemy fe3(mp1.return_faster_pos_x(2), mp1.return_faster_pos_y(2), 12, 0, 11);
                faster_enemy fe4(mp1.return_faster_pos_x(3), mp1.return_faster_pos_y(3), 12, 0, 11);
                faster_enemy fe5(mp1.return_faster_pos_x(4), mp1.return_faster_pos_y(4), 12, 0, 11);
                faster_enemy fe6(mp1.return_faster_pos_x(5), mp1.return_faster_pos_y(5), 12, 0, 11);

                faster_enemy fe7(mp1.return_faster_pos_x(6), mp1.return_faster_pos_y(6), 24, 0, 4);
                faster_enemy fe8(mp1.return_faster_pos_x(7), mp1.return_faster_pos_y(7), 24, 0, 4);
                faster_enemy fe9(mp1.return_faster_pos_x(8), mp1.return_faster_pos_y(8), 24, 0, 4);

                while(1)
                {
                    Sleep(10);
                    e1.update_pos();
                    e1.try_update_pos();
                    Sleep(10);
                    e2.update_pos();
                    e2.try_update_pos();
                    e3.update_pos();
                    e3.try_update_pos();
                    Sleep(10);
                    e4.update_pos();
                    e4.try_update_pos();
                    fe1.update_pos();
                    fe1.try_update_pos();
                    fe2.update_pos();
                    fe2.try_update_pos();
                    fe3.update_pos();
                    Sleep(10);
                    fe3.try_update_pos();
                    fe4.update_pos();
                    fe4.try_update_pos();
                    fe5.update_pos();
                    fe5.try_update_pos();
                    fe6.update_pos();
                    fe6.try_update_pos();
                    e5.update_pos();
                    e5.try_update_pos();
                    Sleep(10);
                    e6.update_pos();
                    e6.try_update_pos();
                    e7.update_pos();
                    e7.try_update_pos();
                    e8.update_pos();
                    e8.try_update_pos();
                    e9.update_pos();
                    e9.try_update_pos();
                    fe7.update_pos();
                    fe7.try_update_pos();
                    Sleep(10);
                    fe8.update_pos();
                    fe8.try_update_pos();
                    fe9.update_pos();
                    fe9.try_update_pos();
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
