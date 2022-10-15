#ifndef SLOW_ENEMY
#define SLOW_ENEMY

#include "Enemy.h"

class SlowEnemy : public Enemy
{
    int pos_x, pos_y, old_pos_x, old_pos_y, way, round,disparity_x, disparity_y, who_used_round, x_or_y;
    bool decision;
    public:
        SlowEnemy(int x, int y):pos_x(x), pos_y(y), old_pos_x(x), old_pos_y(y), way(0), round(0), disparity_x(0), disparity_y(0),decision(false), who_used_round(0), x_or_y(0){};
        ~SlowEnemy(){};
        virtual void UpdatePosition();
        virtual void UpdateConsoleCoordinates();
        virtual void BackToOldPosition();
        virtual bool IsPlayerNear(int, int);
        virtual int GetX();
        virtual int GetY();
};

#endif