#include "Application.h"
#include <iostream>
#include <time.h>
#include "MenuHandler.h"
#include "GameHandler.h"

Application::Application()
{

}

void Application::run()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    MenuHandler menuHandler;

    while (1)
    {
        GameStatus status = menuHandler.run();

        if (status == GameStatus::Start) {
            GameHandler gameHandler;
            gameHandler.run();
        }
        else if (status == GameStatus::About) {
            system("cls");
            std::cout << "About creators:";
            break;
        }
        else {
            exit(0);
        }
    }
}
