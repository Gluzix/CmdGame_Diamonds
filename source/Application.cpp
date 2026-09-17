#include "Application.h"
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include "Console.h"
#include "FileReader.h"
#include "Map.h"
#include "MenuHandler.h"
#include "GameHandler.h"

namespace
{
    // One column and two rows more than the map: the score line goes on the row directly
    // under the board, and nothing is ever written into the last column or the last row, so
    // the console has no reason to wrap or scroll while a round is on screen.
    constexpr int spareColumns = 1;
    constexpr int spareRows = 2;
}

void Application::run()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    // The board is drawn at fixed console coordinates, so the console has to be big enough
    // to hold it before anything is printed. The map is the largest thing the game shows.
    const FileReader mapReader(mapFilePath);
    prepareConsole(mapReader.getWidth() + spareColumns, mapReader.getHeight() + spareRows);

    MenuHandler menuHandler;

    while (true)
    {
        GameStatus status = menuHandler.run();

        if (status == GameStatus::Start) {
            GameHandler gameHandler;
            gameHandler.run();
        }
        else if (status == GameStatus::About) {
            system("cls");
            std::cout << "About creators:" << std::endl;
            std::cout << std::endl << "Press any key to return to the menu..." << std::endl;

            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            _getch();
        }
        else {
            break;
        }
    }

    // The console belongs to whoever started the game, so it goes back the way it was.
    restoreConsole();
}
