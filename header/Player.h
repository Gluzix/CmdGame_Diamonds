#pragma once

#include <Coordinates.h>

class Player
{
public:
    Player(const Coordinates &coords);

    void try_to_move(int);
    void update_plyer();
    void restore_coords();
    int return_pos_x();
    int return_pos_y();

private:
    Coordinates coordinates;
    Coordinates oldCoordinates;
};
