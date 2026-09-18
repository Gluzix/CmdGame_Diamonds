#pragma once

#include <string>
#include <vector>
#include "Map.h"

// Everything that keeps the board from being played, one sentence each, in the order an
// author should fix them. Empty when the board can be played.
std::vector<std::string> findMapProblems(const Map& board);
