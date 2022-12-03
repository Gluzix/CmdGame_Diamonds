#include "Enemy.h"

Enemy::Enemy(int speed)
    : speed(speed)
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

Coordinates Enemy::getCoords()
{
	return coordinates;
}

bool Enemy::isPlayerNear(const Coordinates &coordinates)
{
	return false;
}
