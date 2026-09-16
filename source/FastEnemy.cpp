#include "FastEnemy.h"
#include "Console.h"

FastEnemy::FastEnemy(const Coordinates& beginCoordinates)
    : Enemy(beginCoordinates, 2, 6)
{

}

void FastEnemy::updateConsoleCoordinates()
{
    clearCharAt(oldCoordinates);
    drawCharAt(coordinates, '^', FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    oldCoordinates = coordinates;
}
