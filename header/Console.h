#pragma once

#include <windows.h>
#include "Coordinates.h"

void prepareConsole(int columns, int rows);
void restoreConsole();
void drawCharAt(const Coordinates& coordinates, char character, WORD colour);
void clearCharAt(const Coordinates& coordinates);
