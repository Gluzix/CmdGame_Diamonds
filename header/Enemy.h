#pragma once
#include "Coordinates.h"

class Enemy
{
public:
    Enemy(int speed);
    ~Enemy();
    virtual void updatePosition();
    virtual void updateConsoleCoordinates();
    virtual void backToOldPosition();
    virtual bool isPlayerNear(const Coordinates& coordinates);
    virtual Coordinates getCoords();

private:
    Coordinates coords;
    int speed;
    int way;
};
