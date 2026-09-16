#pragma once

#include "Enemy.h"

class SlowEnemy : public Enemy
{
public:
    SlowEnemy(const Coordinates &beginCoordinates);

    void updateConsoleCoordinates() override;
};
