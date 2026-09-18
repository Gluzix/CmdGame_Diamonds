#include "Application.h"
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
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

    constexpr char mapPath[] = "resources/Map.txt";
    constexpr char winScreenPath[] = "resources/Win.txt";
    constexpr char loseScreenPath[] = "resources/Lose.txt";

    void showScreen(const std::vector<std::string>& lines, const std::string& prompt)
    {
        system("cls");

        for (const std::string& line : lines) {
            std::cout << line << std::endl;
        }

        std::cout << std::endl << prompt << std::endl;

        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        _getch();
    }
}

void Application::run()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    // The board is drawn at fixed console coordinates, so the console has to be big enough
    // to hold it before anything is printed. The map is the largest thing the game shows.
    const FileReader mapReader(mapPath);
    prepareConsole(mapReader.getWidth() + spareColumns, mapReader.getHeight() + spareRows);

    MenuHandler menuHandler;

    while (true)
    {
        GameStatus status = menuHandler.run();

        if (status == GameStatus::Start) {
            const Map board(mapPath);
            GameHandler gameHandler(board);
            const RoundResult result = gameHandler.run();

            if (result == RoundResult::Finished) {
                const FileReader winScreen(winScreenPath);
                showScreen(winScreen.getContent(), "Press any key to return to the menu...");
            }
            else if (result == RoundResult::Caught) {
                const FileReader loseScreen(loseScreenPath);
                showScreen(loseScreen.getContent(), "Press any key to return to the menu...");
            }
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
