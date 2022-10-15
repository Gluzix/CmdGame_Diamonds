#include "Menu.h"
#include <iostream>
using namespace std;
void Menu::enter_space() const
{
           cout<<endl<<endl;
            for(int i=0; i<width/2-5; i++)
            {
                cout<<" ";
            }
}
void Menu::create_menu(){
    FILE *plik;
    plik=fopen(path, "r");
    width = width/height;
    width++;
    for(int i=0; i<height; i++)
    {
        for(int w=0; w<width; w++)
        {
            fscanf(plik, "%c", &start_string[i][w]);
        }
    }
    fclose(plik);
}
void Menu::show_menu(int chc) const
{
        switch(chc)
        {
        case 0:
            for(int i=0; i<height; i++)
            {
                for(int w=0; w<width; w++)
                {
                    cout<<start_string[i][w];
                }
            }
            enter_space();
            cout<<">>Start Game<<"<<endl;
            enter_space();
            cout<<"About Creators"<<endl;
            enter_space();
            cout<<"Exit"<<endl;
        break;
        case 1:
            for(int i=0; i<height; i++)
            {
                for(int w=0; w<width; w++)
                {
                    cout<<start_string[i][w];
                }
            }
            enter_space();
            cout<<"Start Game"<<endl;
            enter_space();
            cout<<">>About Creators<<"<<endl;
            enter_space();
            cout<<"Exit"<<endl;
            break;
        case 2:
            for(int i=0; i<height; i++)
            {
                for(int w=0; w<width; w++)
                {
                    cout<<start_string[i][w];
                }
            }
            enter_space();
            cout<<"Start Game"<<endl;
            enter_space();
            cout<<"About Creators"<<endl;
            enter_space();
            cout<<">>Exit<<"<<endl;
            break;
        }
}
void Menu::show_string() const
{
    for(int i=0; i<height; i++)
    {
        for(int w=0; w<width; w++)
        {
            cout<<start_string[i][w];
        }
    }
}
int Menu::return_height()
{
    return this->height;
}
int Menu::return_width()
{
    return this->width;
}
