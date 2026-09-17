#pragma once

#include <vector>
#include <FileReader.h>
#include "Coordinates.h"

inline constexpr char mapFilePath[] = "resources/Map.txt";

class Map
{
    public:
        void drawMap();
        bool isObstacleForEnemy(const Coordinates& coords) const;
        bool isObstacleForPlayer(const Coordinates& coords) const;

        const Coordinates& getPlayerCoords() const;

        bool hasPlayerTakenDiamond(const Coordinates& coords);
        bool hasPlayerSwitchedGate(const Coordinates& coords) const;
        int getPoints() const;
        void removeBarriers();
        void clearSpawnMarkers();
        void redrawTile(const Coordinates& coords) const;

        bool hasPlayerFinished(const Coordinates& coords) const;

        const FileReader& getFileReader() const;

private:
    bool isInside(const Coordinates& coords) const;
    char charAt(const Coordinates& coords) const;

    std::vector<Coordinates> barrierPos{};

    Coordinates playerPos{ 0, 0 };

    int points{0};

    FileReader fileReader{ mapFilePath };
};
