#include "Coordinates.h"

inline Coordinates::Coordinates(int x, int y) {
    this->x = x;
    this->y = y;
}

inline Coordinates::Coordinates() {
    this->x = -1;
    this->y = -1;
}
