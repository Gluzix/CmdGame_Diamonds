#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
class enemy
{
    public:
        enemy();
        virtual ~enemy();
        virtual void update_pos();
        virtual void try_update_pos();
        virtual void return_to_old_pos();
        virtual bool check_if_player_is_near(int, int);
        virtual int return_pos_x();
        virtual int return_pos_y();
};
#endif // ENEMY_H
