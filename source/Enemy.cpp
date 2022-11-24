#include "Enemy.h"

Enemy::Enemy(int speed)
    : speed(speed)
{

}

Enemy::~Enemy() 
{

}

void Enemy::updatePosition()
{
    if (who_used_round == 1)
    {
        speed = 0;
    }
    if (speed == 4)
    {
        if (way == 0) {
            coords.y++;
        }
        else if (way == 1) {
            coords.x++;
        }
        else if (way == 2) {
            coords.y--;
        }
        else if (way == 3) {
            coords.x--;
        }
        speed = 0;
    }
    else {
        speed++;
    }
    who_used_round = 0;
}

void Enemy::updateConsoleCoordinates()
{

}

void Enemy::backToOldPosition()
{

}

Coordinates Enemy::getCoords()
{
	return Coordinates();
}

bool Enemy::isPlayerNear(const Coordinates &coordinates)
{
	return false;
}
