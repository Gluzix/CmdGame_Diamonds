#include "GameHandler.h"
#include "FastEnemy.h"
#include "FastestEnemy.h"
#include "Player.h"
#include "Punctation.h"
#include "SlowEnemy.h"
#include <conio.h>
#include <iostream>
#include <Windows.h>

namespace
{
    constexpr int frameTimeMs = 100;
    constexpr int blockedEnemyRetries = 4;
}

void GameHandler::run()
{
    map.drawMap();
    prepareEnemies();

    Punctation punctation(map.getPoints(), map.getFileReader().getHeight());
    punctation.show();

    Player player(map.getPlayerCoords());

    bool hasWon = false;

    while (true)
    {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            return;
        }

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

        // isObstacleForPlayer() treats 'S', 'O', 'U' and 'T' as walls, so the lever and
        // the exit have to be answered before the position is restored. The player bumps
        // into that tile to use it and bounces back.
        if (map.hasPlayerTookDiamond(player.pos())) {
            punctation.update();
            punctation.show();
        }

        const bool hasEveryDiamond = punctation.get() == map.getPoints();

        if (map.hasPlayerFinished(player.pos()) && hasEveryDiamond) {
            hasWon = true;
            break;
        }

        // The lever deliberately does NOT require every diamond: resources/Map.txt puts
        // one diamond inside the sealed OUT chamber, so demanding a full score before the
        // barriers open would deadlock the round. Only the exit checks the score.
        if (map.hasPlayerSwitchedGate(player.pos())) {
            map.removeBarriers();
        }

        if (map.isObstacleForPlayer(player.pos())) {
            player.restoreCoordinates();
        }

        player.updatePlayer();

        if (isPlayerCaught(player.pos())) {
            break;
        }

        moveEnemies(player.pos());

        if (isPlayerCaught(player.pos())) {
            break;
        }

        Sleep(frameTimeMs);
    }

    showEndScreen(hasWon ? "resources/Win.txt" : "resources/Loose.txt");
}

void GameHandler::prepareEnemies()
{
    enemies.clear();

    int width = 0;
    int height = 0;

    for (const std::string& line : map.getFileReader().getContent()) {
        for (const char& ch : line) {
            if (ch == '&') {
                enemies.push_back(std::make_shared<SlowEnemy>(Coordinates(width, height)));
            }
            else if (ch == '^') {
                enemies.push_back(std::make_shared<FastEnemy>(Coordinates(width, height)));
            }
            else if (ch == '%') {
                enemies.push_back(std::make_shared<FastestEnemy>(Coordinates(width, height)));
            }
            width++;
        }
        width = 0;
        height++;
    }
}

void GameHandler::moveEnemies(const Coordinates& playerCoordinates)
{
    for (std::shared_ptr<Enemy>& enemy : enemies) {
        if (!enemy->shouldMove()) {
            continue;
        }

        if (enemy->canChasePlayer() && enemy->isPlayerNear(playerCoordinates)) {
            enemy->tryToFollowPlayer(playerCoordinates);
        }
        else {
            enemy->updatePosition();
        }

        if (map.isObstacleForEnemy(enemy->getCoords())) {
            enemy->backToOldPosition();

            for (int retry = 0; retry < blockedEnemyRetries; retry++) {
                enemy->chooseNewWay();
                enemy->updatePosition();

                if (!map.isObstacleForEnemy(enemy->getCoords())) {
                    break;
                }

                enemy->backToOldPosition();
            }
        }

        if (enemy->hasMoved()) {
            enemy->updateConsoleCoordinates();
        }
    }
}

bool GameHandler::isPlayerCaught(const Coordinates& playerCoordinates) const
{
    for (const std::shared_ptr<Enemy>& enemy : enemies) {
        if (enemy->getCoords() == playerCoordinates) {
            return true;
        }
    }

    return false;
}

void GameHandler::showEndScreen(const std::string& pathToFile) const
{
    system("cls");

    FileReader fileReader(pathToFile);

    for (const std::string& line : fileReader.getContent()) {
        std::cout << line << std::endl;
    }

    std::cout << std::endl << "Press any key to return to the menu..." << std::endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
}
