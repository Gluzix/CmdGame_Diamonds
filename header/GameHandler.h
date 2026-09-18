#pragma once

#include "Enemy.h"
#include "Map.h"
#include <string>
#include <vector>
#include <FileReader.h>
#include <memory>

// How a round ended. Whoever started it decides what happens next.
enum class RoundResult {
	Finished,
	Caught,
	Quit
};

class GameHandler
{
public:
	explicit GameHandler(const Map& board, int levelNumber, int levelCount);

	RoundResult run();

private:
	void prepareEnemies();
	void moveEnemies(const Coordinates& playerCoordinates);
	bool isPlayerCaught(const Coordinates& playerCoordinates) const;

	std::vector<std::unique_ptr<Enemy>> enemies;

	Map map;
	const int levelNumber;
	const int levelCount;
};
