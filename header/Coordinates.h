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

    bool operator==(const Coordinates& other) const = default;

    int x{ -1 };
    int y{ -1 };
};
