#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAP_SIZE_X 32
#define MAP_SIZE_Y 5
#define MAX_NUMBER_OF_UNITS 1002

#include "load_status.h"
#include "menu.h"
#include "train.h"
#include "move.h"
#include "attack.h"
#include "map.h"
#include "display_map.h"
#include "list.h"
#include "save.h"
#include "mining.h"

int time_left; // number of seconds the player program is allowed to run;

pthread_t thread; // thread identifier used for time control over the player round;

int temp[MAP_SIZE_Y][MAP_SIZE_X+1]; //temporary array to hold chars read from the file
int map_data[MAP_SIZE_Y][MAP_SIZE_X]; //target array to hold int values representing the map

long gold = 0; // holds the amount of gold
au active_units[MAX_NUMBER_OF_UNITS] = { 0 }; // holds information on player and enemy active units;
char type; // holds the type of the unit to be trained
int units_on_the_map_counter = 0; // holds the number of units currently present on the map

void *timer(void *arg)
{
    while (1)
	{
        /* Check if time is up in one second intervals */
        sleep(1);

        /* Update timer */
        if (time_left > 0)
		{
            time_left--;
            if (time_left == 0)
			{
                save(&gold, &units_on_the_map_counter, active_units);
			    pthread_join(thread, NULL);
				exit(0);
			}
        }
    }

    return NULL;
}

int main(int argc, char* argv[])
{
	
	int limit; // number of seconds a round is permitted to last
	if (!argv[4])
		limit = 5;
	else
		limit = atoi(argv[4]); // default = 5 seconds, as indicated in the instructions

	/* establishing thread for time control over gameplay */
    int ret = pthread_create(&thread, NULL, timer, NULL);
    if (ret)
        return 1;

	/* erase rozkazy.txt by opening it in write mode */
	FILE *fptr = fopen(argv[3], "w");
	fclose(fptr);

	/* reading status and map data from files, updating gold if workers are present at the mine */
	map(argv[1], map_data, temp); // update map
	
	/* if no status.txt exists, assume default game start settings */
	FILE *fptr2 = fopen(argv[2], "r");
	if (!fptr2)
	{
	    gold = 2000;

        strcpy(active_units[0].affiliation, "P");
	    strcpy(active_units[0].unit_type, "B");
        active_units[0].unit_id = 0;
        active_units[0].x_coord = 0;
        active_units[0].y_coord = 0;
        active_units[0].current_stamina = 200;
        strcpy(active_units[0].is_base_busy, "0");

        strcpy(active_units[1].affiliation, "E");
	    strcpy(active_units[1].unit_type, "B");
        active_units[1].unit_id = 1;
        active_units[1].x_coord = MAP_SIZE_X-1;
        active_units[1].y_coord = MAP_SIZE_Y-1;
        active_units[1].current_stamina = 200;
        strcpy(active_units[1].is_base_busy, "0");

        units_on_the_map_counter = 2;
	}
	else
	{
		load_status(argv[2], &units_on_the_map_counter, &gold, active_units); // otherwise, read data from status.txt
	}

	gold += mining(map_data, active_units, &units_on_the_map_counter); // update gold

	menu(&gold, &units_on_the_map_counter); // display the user interface

	while (1)
	{
        time_left = limit;
    
		printf("\n >>> ");

		/* user interface logic */
		char line[1024];
		if (!fgets(line, sizeof(line), stdin))
		{
			fprintf(stderr, "input error\n");
			return 1;
		}

		char option[1024];
		if (sscanf(line, "%1023s", option) != 1)
			continue;

		if (strcmp(option, "K") == 0)
		{
			type = 'K';
        	train(argv[3], &gold, &type, active_units, &units_on_the_map_counter);
		}	
		if (strcmp(option, "S") == 0)
		{
			type = 'S';
        	train(argv[3], &gold, &type, active_units, &units_on_the_map_counter);
		}	
		if (strcmp(option, "A") == 0)
		{
			type = 'A';
        	train(argv[3], &gold, &type, active_units, &units_on_the_map_counter);
		}	
		if (strcmp(option, "P") == 0)
		{
			type = 'P';
        	train(argv[3], &gold, &type, active_units, &units_on_the_map_counter);
		}
		if (strcmp(option, "R") == 0)
		{
			type = 'R';
        	train(argv[3], &gold, &type, active_units, &units_on_the_map_counter);
		}
		if (strcmp(option, "C") == 0)
		{
			type = 'C';
        	train(argv[3], &gold, &type, active_units, &units_on_the_map_counter);
		}	
		if (strcmp(option, "W") == 0)
		{
			type = 'W';
        	train(argv[3], &gold, &type, active_units, &units_on_the_map_counter);
		}
		if (strcmp(option, "MOVE") == 0)
			move(argv[3], active_units, &units_on_the_map_counter, map_data);
		if (strcmp(option, "ATTACK") == 0)
			attack(argv[3], active_units, &units_on_the_map_counter);
        if (strcmp(option, "MAP") == 0)
			display_map(map_data);
        if (strcmp(option, "LIST") == 0)
			list(active_units, &units_on_the_map_counter);
        if (strcmp(option, "MENU") == 0)
            menu(&gold, &units_on_the_map_counter);
		if (strcmp(option, "SAVE") == 0)
		{
			save(&gold, &units_on_the_map_counter, active_units);
			pthread_join(thread, NULL);
			exit(0);
		}
	}

    return 0;
}