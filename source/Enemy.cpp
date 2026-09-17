#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy(const Coordinates& beginCoordinates, int moveEveryNTicks, int recognitionDistance)
    : coordinates(beginCoordinates)
    , oldCoordinates(beginCoordinates)
    , moveEveryNTicks(moveEveryNTicks)
    , recognitionDistance(recognitionDistance)
{

}

bool Enemy::shouldMove()
{
    tickCounter++;

    if (tickCounter >= moveEveryNTicks) {
        tickCounter = 0;
        return true;
    }

    return false;
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

Coordinates Enemy::getCoords() const
{
    return coordinates;
}

bool Enemy::isPlayerNear(const Coordinates &playerCoordinates) const
{
    int differenceX = abs(playerCoordinates.x - this->coordinates.x);
    int differenceY = abs(playerCoordinates.y - this->coordinates.y);

    return differenceX <= recognitionDistance && differenceY <= recognitionDistance;
}

void Enemy::updateWay(Way newWay)
{
    this->way = newWay;
}

void Enemy::reverseWay()
{
    switch (way) {
    case Way::Up:
        way = Way::Down;
        break;
    case Way::Down:
        way = Way::Up;
        break;
    case Way::Left:
        way = Way::Right;
        break;
    case Way::Right:
        way = Way::Left;
        break;
    }
}

bool Enemy::hasMoved() const
{
    return coordinates != oldCoordinates;
}

bool Enemy::canChasePlayer() const
{
    return true;
}

void Enemy::chooseNewWay()
{
    way = static_cast<Way>(rand() % 4);
}
