#ifndef SLOW_ENEM_H
#define SLOW_ENEM_H
#include "enemy.h"

class slow_enem : public enemy
{
    int pos_x, pos_y, old_pos_x, old_pos_y, way, round,disparity_x, disparity_y, who_used_round, x_or_y;
    bool decision;
    public:
        slow_enem(int x, int y):pos_x(x), pos_y(y), old_pos_x(x), old_pos_y(y), way(0), round(0), disparity_x(0), disparity_y(0),decision(false), who_used_round(0), x_or_y(0){};
        ~slow_enem(){};
        virtual void update_pos();
        virtual void try_update_pos();
        virtual void return_to_old_pos();
        virtual bool check_if_player_is_near(int, int);
        virtual int return_pos_x();
        virtual int return_pos_y();
};

#endif // SLOW_ENEM_H
