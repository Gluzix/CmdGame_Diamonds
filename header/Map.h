#pragma once

#include <string>
#include <vector>
#include <FileReader.h>
#include "Coordinates.h"


class Map
{
    public:
        Map();
        void drawMap();
        bool isObstacleForEnemy(const Coordinates& coords) const;
        bool isObstacleForPlayer(const Coordinates& coords) const;

        const Coordinates& getPlayerCoords();

        bool hasPlayerTookDiamond(const Coordinates& coords);
        bool hasPlayerSwitchedGate(const Coordinates& coords) const;
        int getPoints();
        void removeBarriers();

        bool hasPlayerFinished(const Coordinates& coords) const;

        const FileReader& getFileReader();

private:
    bool isInside(const Coordinates& coords) const;
    char charAt(const Coordinates& coords) const;

    void drawAsteriks();
    void drawDollar();
    void drawAmpersand();
    void drawHashtag();
    void drawCommercialAt();
    void drawCaret();
    void drawPercent();

    std::vector<std::string> startString{};
    std::vector<Coordinates> barrierPos{};

    Coordinates playerPos{ 0, 0 };

    int points{0};

    FileReader fileReader{ "resources/Map.txt" };
};
