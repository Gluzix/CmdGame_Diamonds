#include "Application.h"
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
#include "FileReader.h"
#include "MenuHandler.h"

Application::Application()
{

}

void Application::run()
{
    srand(time(NULL));
    int menuIndex = 0;
    std::string startPathStr = "resources/Start.txt";
    std::string mapPathStr = "resources/Map.txt";
    FileReader reader(mapPathStr);
    Map mp1;

    int way = 0;

    MenuHandler menuHandler;

    while (1)
    {
        GameStatus status = menuHandler.run();

        switch (status) {
            case GameStatus::Start: break;
            case GameStatus::About: break;
            case GameStatus::Exit: break;
            default: break;
        }

        if (x == 0)
        {
            mp1.drawMap();

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

            while (1)
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
        else if (x == 1)
        {
            system("cls");
            std::cout << "About creators:";
            break;//something to do
        }
        else if (x == 2) exit(0);//something to do
    }
}
