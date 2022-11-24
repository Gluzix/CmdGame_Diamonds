#pragma once

class Coordinates
{
public:
    Coordinates(int x, int y);
    Coordinates();

    Coordinates operator =(const Coordinates& coords) {
        return Coordinates(coords.x, coords.y);
    }

    bool operator ==(const Coordinates& coords) {
        return this->x == coords.x && this->y == coords.y;
    }

    int x;
    int y;
};

bool operator ==(const Coordinates& coords1, const Coordinates& coords2) {
    return coords1.x == coords2.x && coords1.y == coords2.y;
}
