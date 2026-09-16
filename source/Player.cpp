#include "Player.h"
#include "Console.h"

Player::Player(const Coordinates& coords)
    : coordinates(coords)
    , oldCoordinates(coords)
{

}

void Player::tryToMove(Way way)
{
    switch(way)
    {
    case Way::Up:
        coordinates.y--;
        break;
    case Way::Down:
        coordinates.y++;
        break;
    case Way::Left:
        coordinates.x--;
        break;
    case Way::Right:
        coordinates.x++;
        break;
    }
}

void Player::restoreCoordinates()
{
    coordinates = oldCoordinates;
}

const Coordinates& Player::pos()
{
    return coordinates;
}

void Player::updatePlayer()
{
    clearCharAt(oldCoordinates);
    drawCharAt(coordinates, '@', FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    oldCoordinates = coordinates;
}
