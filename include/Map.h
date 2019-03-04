#ifndef MAP_H
#define MAP_H
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
class Map
{
    char**start_string;
    char *path;
    int *faster_enemy_pos_x;
    int *faster_enemy_pos_y;
    int *slow_enemy_pos_x;
    int *slow_enemy_pos_y;
    int width, height, choice, player_pos_x, player_pos_y, counter_of_slow_enemy_pos, counter_of_faster_enemy_pos, points, counter_of_barriers;
    int *barrier_pos_x;
    int *barrier_pos_y;
    public:
        Map(int x, int y, const char *p):width(x), height(y), choice(0), player_pos_x(0), player_pos_y(0), counter_of_slow_enemy_pos(1),
        counter_of_faster_enemy_pos(1), points(0), counter_of_barriers(1)
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
            faster_enemy_pos_x=(int*)malloc(counter_of_faster_enemy_pos*sizeof(int));
            faster_enemy_pos_y=(int*)malloc(counter_of_faster_enemy_pos*sizeof(int));
            slow_enemy_pos_x=(int*)malloc(counter_of_slow_enemy_pos*sizeof(int));
            slow_enemy_pos_y=(int*)malloc(counter_of_slow_enemy_pos*sizeof(int));
            barrier_pos_x=(int*)malloc(counter_of_barriers*sizeof(int));
            barrier_pos_y=(int*)malloc(counter_of_barriers*sizeof(int));
        }
        ~Map()
        {
            for(int i=0; i<height; i++)
            {
                free(start_string[i]);
            }
            free(start_string);
            free(path);
            free(faster_enemy_pos_x);
            free(faster_enemy_pos_y);
            free(slow_enemy_pos_x);
            free(slow_enemy_pos_y);
            free(barrier_pos_x);
            free(barrier_pos_y);
        }
        void create_map();
        void show_map();
        bool check_if_obstacle_for_slow_enem(int, int, int);
        bool check_if_obstacle_for_fast_enem(int, int, int);
        bool check_if_obstacle_for_player(int, int);
        int return_slow_enem_pos_x(int);
        int return_slow_enem_pos_y(int);
        int return_faster_enem_pos_x(int);
        int return_faster_enem_pos_y(int);
        int return_player_pos_x();
        int return_player_pos_y();
        int return_counter_of_slow_enem_pos();
        int return_counter_of_faster_enem_pos();
        int return_nmbr_of_required_points();
        bool check_if_player_lost(int, int);
        bool check_if_slow_enem_meet_enem(int, int, int);
        bool check_if_faster_enem_meet_enem(int, int, int);
        bool check_if_player_got_diamond(int, int);
        bool check_if_player_turn_on_switch(int, int);
        bool check_if_player_got_out(int, int);
        void delete_barrier();
};
#endif // MAP_H
