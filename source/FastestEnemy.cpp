#include "FastestEnemy.h"
#include "Console.h"

// The 0 recognition distance is never consulted: canChasePlayer() below returns false, and
// GameHandler::moveEnemies short-circuits on that before Enemy::isPlayerNear is ever
// reached, so this enemy just bounces along its line whatever the number says.
FastestEnemy::FastestEnemy(const Coordinates& beginCoordinates)
    : Enemy(beginCoordinates, 1, 0)
{
    updateWay(Way::Up);
}

bool FastestEnemy::canChasePlayer() const
{
    return false;
}

void FastestEnemy::chooseNewWay()
{
    reverseWay();
}

void FastestEnemy::updateConsoleCoordinates()
{
    clearCharAt(oldCoordinates);
    drawCharAt(coordinates, '%', FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    oldCoordinates = coordinates;
}
