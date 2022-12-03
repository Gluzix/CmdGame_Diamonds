#pragma once

#include "Enemy.h"

class SlowEnemy : public Enemy
{
public:
    SlowEnemy(int speed);

    virtual void updateConsoleCoordinates();
    virtual bool isPlayerNear(int, int);

};
