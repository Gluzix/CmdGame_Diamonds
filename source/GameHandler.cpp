#include "GameHandler.h"
#include "FastEnemy.h"
#include "SlowEnemy.h"
#include <Windows.h>

GameHandler::GameHandler()
{
}

void GameHandler::run()
{
    map.drawMap();
    prepareEnemies();

    Player player(map.getPlayerCoords());

    while (1)
    {
        if (GetAsyncKeyState(VK_UP)) {
            player.tryToMove(Way::Up);
        }
        else if (GetAsyncKeyState(VK_DOWN)) {
            player.tryToMove(Way::Down);
        }
        else if (GetAsyncKeyState(VK_LEFT)) {
            player.tryToMove(Way::Left);
        }
        else if (GetAsyncKeyState(VK_RIGHT)) {
            player.tryToMove(Way::Right);
        }

        if (map.isObstacleForPlayer(player.pos()))
        {
            player.restoreCoordinates();
        }
        player.updatePlayer();

        for (auto &enemy : enemies) {
            if (enemy->isPlayerNear(player.pos())) {
                enemy->tryToFollowPlayer(player.pos());
            }
        }

        //for (int i = 13; i < 17; i++)
        //{
        //    if (!((FastEnemy*)container[i]->IsPlayerNear(player.return_pos_x(), player.return_pos_y())))
        //    {
        //        ((FastEnemy*)container[i])->UpdatePosition();
        //    }

        //    while (!mp1.check_if_obstacle_for_fast_enem(((FastEnemy*)container[i])->GetX(), ((FastEnemy*)container[i])->GetY(), i) ||
        //        !mp1.check_if_faster_enem_meet_enem(((FastEnemy*)container[i])->GetX(), ((FastEnemy*)container[i])->GetY(), i))
        //    {
        //        ((FastEnemy*)container[i])->BackToOldPosition();
        //        if (!((FastEnemy*)container[i]->IsPlayerNear(player.return_pos_x(), player.return_pos_y())))
        //        {
        //            ((FastEnemy*)container[i])->UpdatePosition();
        //        }
        //    }
        //    ((FastEnemy*)container[i])->UpdateConsoleCoordinates();
        //}
        Sleep(100);
    }
}

void GameHandler::prepareEnemies()
{
    enemies.clear();

    int width = 0;
    int height = 0;

    for (std::string line : map.getFileReader().getContent()) {
        for (const char& ch : line) {
            if (ch == '&') {
                enemies.push_back(std::shared_ptr<Enemy>(new FastEnemy(Coordinates(width, height))));
            }
            else if (ch == '^') {
                enemies.push_back(std::shared_ptr<Enemy>(new SlowEnemy(Coordinates(width, height))));
            }
            width++;
        }
        width = 0;
        height++;
    }
}
