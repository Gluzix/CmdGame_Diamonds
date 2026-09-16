#include "FastestEnemy.h"
#include "Console.h"

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
