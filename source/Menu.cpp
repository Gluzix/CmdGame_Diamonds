#include "Menu.h"
#include <array>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>

namespace
{
    constexpr std::array<std::string_view, 3> options{ "Start Game", "About Creators", "Exit" };
}

void Menu::show(int index) const
{
    showReadMenuOnScreen();

    for (int option = 0; option < static_cast<int>(options.size()); option++) {
        std::cout << std::endl;

        if (option == index) {
            std::cout << ">>" << options[option] << "<<" << std::endl;
        }
        else {
            std::cout << options[option] << std::endl;
        }
    }
}

void Menu::showReadMenuOnScreen() const
{
    system("cls");

    for (const std::string& element : fileReader.getContent()) {
        std::cout << element << std::endl;
    }
}
