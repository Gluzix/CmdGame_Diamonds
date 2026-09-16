#pragma once

#include <windows.h>
#include "Coordinates.h"

void drawCharAt(const Coordinates& coordinates, char character, WORD colour);
void clearCharAt(const Coordinates& coordinates);
