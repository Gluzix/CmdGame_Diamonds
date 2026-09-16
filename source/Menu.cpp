#include "Menu.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

void Menu::show(int index) const
{
    switch (index)
    {
    case 0:
        chooseStart();
        break;
    case 1:
        chooseAbout();
        break;
    case 2:
        chooseExit();
        break;
    }
}

void Menu::showReadMenuOnScreen() const
{
    system("cls");

    for (const std::string& element : fileReader.getContent()) {
        std::cout << element << std::endl;
    }
}

void Menu::chooseStart() const
{
    showReadMenuOnScreen();

    std::cout << std::endl;
    std::cout << ">>Start Game<<" << std::endl;
    std::cout << std::endl;
    std::cout << "About Creators" << std::endl;
    std::cout << std::endl;
    std::cout << "Exit" << std::endl;
}

void Menu::chooseAbout() const
{
    showReadMenuOnScreen();

    std::cout << std::endl;
    std::cout << "Start Game" << std::endl;
    std::cout << std::endl;
    std::cout << ">>About Creators<<" << std::endl;
    std::cout << std::endl;
    std::cout << "Exit" << std::endl;
}

void Menu::chooseExit() const
{
    showReadMenuOnScreen();

    std::cout << std::endl;
    std::cout << "Start Game" << std::endl;
    std::cout << std::endl;
    std::cout << "About Creators" << std::endl;
    std::cout << std::endl;
    std::cout << ">>Exit<<" << std::endl;
}
