#ifndef PLAYER_H
#define PLAYER_H
class player
{
    int pos_x, pos_y, old_pos_x, old_pos_y;
    public:
        player(int x ,int y): pos_x(x), pos_y(y), old_pos_x(x), old_pos_y(y){}
        ~player(){}
        void try_to_move(int);
        void update_plyer();
        void restore_coords();
        int return_pos_x();
        int return_pos_y();
};

#endif // PLAYER_H
