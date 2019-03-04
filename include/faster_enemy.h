#ifndef FASTER_ENEMY_H
#define FASTER_ENEMY_H
class faster_enemy
{
    int pos_y, old_pos_y, pos_x, old_pos_x, which_way, his_way, counter, counter_sc;
    public:
        faster_enemy(int x, int y, int hisy):pos_y(y), old_pos_y(y), pos_x(x), old_pos_x(x), which_way(0), his_way(hisy), counter(0), counter_sc(0){}
        void update_pos();
        void try_update_pos();
        void return_to_old_pos();
        int return_pos_y();
        int return_pos_x();
};
#endif // FASTER_ENEMY_H
