#include "Application.h"
#include <conio.h>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include "MenuHandler.h"
#include "GameHandler.h"

void Application::run()
{
    srand(static_cast<unsigned int>(time(nullptr)));

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
            return;
        }
    }
}
