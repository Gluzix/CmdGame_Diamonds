#pragma once

class Coordinates
{
public:
    Coordinates() = default;

    Coordinates(int x, int y)
        : x(x)
        , y(y)
    {
    }

    int x{ -1 };
    int y{ -1 };
};

inline bool operator ==(const Coordinates& coords1, const Coordinates& coords2)
{
    return coords1.x == coords2.x && coords1.y == coords2.y;
}

inline bool operator !=(const Coordinates& coords1, const Coordinates& coords2)
{
    return !(coords1 == coords2);
}
