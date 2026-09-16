#pragma once

#include <string>
#include <vector>
#include <FileReader.h>
#include "Coordinates.h"


class Map
{
    public:
        void drawMap();
        bool isObstacleForEnemy(const Coordinates& coords) const;
        bool isObstacleForPlayer(const Coordinates& coords) const;

        const Coordinates& getPlayerCoords();

        bool hasPlayerTookDiamond(const Coordinates& coords);
        bool hasPlayerSwitchedGate(const Coordinates& coords) const;
        int getPoints();
        void removeBarriers();
        void clearEnemySpawns();
        void redrawTile(const Coordinates& coords) const;

        bool hasPlayerFinished(const Coordinates& coords) const;

        const FileReader& getFileReader();

private:
    bool isInside(const Coordinates& coords) const;
    char charAt(const Coordinates& coords) const;

    std::vector<Coordinates> barrierPos{};

    Coordinates playerPos{ 0, 0 };

    int points{0};

    FileReader fileReader{ "resources/Map.txt" };
};
