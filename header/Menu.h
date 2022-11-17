#pragma once

#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

class Menu
{
    char**start_string;
    char *path;
    int width, height, choice;
    public:
        Menu(int x, int y, const char *p):width(x), height(y), choice(0)
        {
            int dlugosc;
            dlugosc=strlen(p);
            path=(char*)malloc(dlugosc*sizeof(char));
            strcpy(path, p);
            //--alokacja napisu startowego.
            start_string=(char**)malloc(height*sizeof(char*));
            for(int i=0; i<height; i++)
            {
                start_string[i]=(char*)malloc(width*sizeof(char));
            }
        }
        ~Menu()
        {
            for(int i=0; i<height; i++)
            {
                free(start_string[i]);
            }
            free(start_string);
            free(path);
        }
        void create_menu();
        void show_menu(int) const;
        void show_string() const;
        void enter_space() const;
        int return_width();
        int return_height();
};
#endif // MENU_H
