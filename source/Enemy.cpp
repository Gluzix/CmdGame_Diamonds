#include "Enemy.h"
#include <math.h>

Enemy::Enemy(const Coordinates& beginCoordinates, int speed, int recognitionDistance)
    : coordinates(beginCoordinates)
    , oldCoordinates(beginCoordinates)
    , speed(speed)
    , recognitionDistance(recognitionDistance)
{

}

void Enemy::updatePosition()
{
    switch (way) {
    case Way::Up:
        coordinates.y--;
        break;
    case Way::Down:
        coordinates.y++;
        break;
    case Way::Left:
        coordinates.x--;
        break;
    case Way::Right:
        coordinates.x++;
        break;
    }

    if (speed == 4) {
        speed = 0;
    }
    else {
        speed++;
    }
}

void Enemy::backToOldPosition()
{
    coordinates = oldCoordinates;
}

void Enemy::tryToFollowPlayer(const Coordinates& playerCoordinates)
{
    int differenceX = this->coordinates.x - playerCoordinates.x;
    int differenceY = this->coordinates.y - playerCoordinates.y;

    if (abs(differenceX) >= abs(differenceY)) {
        if (differenceX < 0) {
            updateWay(Way::Right);
        } else {
            updateWay(Way::Left);
        }
    } else {
        if (differenceY < 0) {
            updateWay(Way::Down);
        }
        else {
            updateWay(Way::Up);
        }
    }

    updatePosition();
}

Coordinates Enemy::getCoords()
{
	return coordinates;
}

bool Enemy::isPlayerNear(const Coordinates &playerCoordinates)
{
    int differenceX = abs(playerCoordinates.x - this->coordinates.x);
    int differenceY = abs(playerCoordinates.y - this->coordinates.y);

    if (differenceX <= recognitionDistance || differenceY <= recognitionDistance) {
        return true;
    }

	return false;
}

void Enemy::updateWay(Way way)
{
    this->way = way;
}
