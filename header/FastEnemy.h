#pragma once

#include "Enemy.h"

class FastEnemy : public Enemy
{
public:
    FastEnemy(const Coordinates &beginCoordinates);

    void updateConsoleCoordinates() override;
};
