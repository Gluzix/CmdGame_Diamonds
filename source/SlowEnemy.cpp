#include "SlowEnemy.h"
#include "Console.h"

SlowEnemy::SlowEnemy(const Coordinates& beginCoordinates)
    : Enemy(beginCoordinates, 4, 4)
{

}

void SlowEnemy::updateConsoleCoordinates()
{
    clearCharAt(oldCoordinates);
    drawCharAt(coordinates, '&', FOREGROUND_RED | FOREGROUND_INTENSITY);
    oldCoordinates = coordinates;
}
