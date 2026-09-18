#include "GameHandler.h"
#include "FastEnemy.h"
#include "FastestEnemy.h"
#include "Player.h"
#include "Score.h"
#include "SlowEnemy.h"
#include <cstdlib>
#include <Windows.h>

namespace
{
    constexpr int frameTimeMs = 100;
    constexpr int blockedEnemyRetries = 4;

    constexpr int roundKeys[] = { VK_ESCAPE, VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT };

    // GetAsyncKeyState() also reports a key pressed at any time since it was last asked about
    // that key. Without this, a key pressed before the round (Esc in the menu, or on the screen
    // after the last round) acts on the first frame, and Esc there gives the game up the
    // moment the board appears.
    void forgetEarlierKeyPresses()
    {
        for (const int key : roundKeys) {
            GetAsyncKeyState(key);
        }
    }
}

// A copy: whoever starts the round keeps the board as it was read, so the next attempt at
// this level starts from that and not from what this round did to it.
GameHandler::GameHandler(const Map& board)
    : map(board)
{
}

RoundResult GameHandler::run()
{
    forgetEarlierKeyPresses();

    map.drawMap();
    prepareEnemies();

    // drawMap() has already painted the '&', '^', '%' and '@' glyphs and recorded where the
    // player starts, so the spawn markers can leave the map data now. Otherwise every enemy
    // spawn cell stays a phantom wall for the rest of the round - the player could never
    // walk through it and no enemy could re-enter it - and the '@' left on the start square
    // is repainted as a second player the moment the real one steps off it.
    map.clearSpawnMarkers();

    Score score(map.getPoints(), map.getFileReader().getHeight());
    score.show();

    Player player(map.getPlayerCoords());

    while (true)
    {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            return RoundResult::Quit;
        }

        // At the top of a frame the player's drawn cell and logical cell are the same, so
        // this is the tile that has to be repainted if the player walks off it.
        const Coordinates previousPosition = player.pos();

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
        if (map.hasPlayerTakenDiamond(player.pos())) {
            score.update();
            score.show();
        }

        const bool hasEveryDiamond = score.get() == map.getPoints();

        if (map.hasPlayerFinished(player.pos()) && hasEveryDiamond) {
            return RoundResult::Finished;
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

        if (previousPosition != player.pos()) {
            map.redrawTile(previousPosition);
        }

        if (isPlayerCaught(player.pos())) {
            return RoundResult::Caught;
        }

        moveEnemies(player.pos());

        if (isPlayerCaught(player.pos())) {
            return RoundResult::Caught;
        }

        Sleep(frameTimeMs);
    }
}

void GameHandler::prepareEnemies()
{
    enemies.clear();

    int x = 0;
    int y = 0;

    for (const std::string& line : map.getFileReader().getContent()) {
        for (const char& ch : line) {
            if (ch == '&') {
                enemies.push_back(std::make_unique<SlowEnemy>(Coordinates(x, y)));
            }
            else if (ch == '^') {
                enemies.push_back(std::make_unique<FastEnemy>(Coordinates(x, y)));
            }
            else if (ch == '%') {
                enemies.push_back(std::make_unique<FastestEnemy>(Coordinates(x, y)));
            }
            x++;
        }
        x = 0;
        y++;
    }
}

void GameHandler::moveEnemies(const Coordinates& playerCoordinates)
{
    for (const std::unique_ptr<Enemy>& enemy : enemies) {
        if (!enemy->shouldMove()) {
            continue;
        }

        const Coordinates previousPosition = enemy->getCoords();

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
            // updateConsoleCoordinates() blanks the cell the enemy left, which would rub
            // out a diamond it walked over, so put the map's own tile back afterwards.
            enemy->updateConsoleCoordinates();
            map.redrawTile(previousPosition);
        }
    }
}

bool GameHandler::isPlayerCaught(const Coordinates& playerCoordinates) const
{
    for (const std::unique_ptr<Enemy>& enemy : enemies) {
        if (enemy->getCoords() == playerCoordinates) {
            return true;
        }
    }

    return false;
}
