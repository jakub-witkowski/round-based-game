#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
    char affiliation[2];
    char unit_type[2];
    int unit_id;
    int x_coord;
    int y_coord;
    int current_stamina;
    int remaining_movement;
    int attack_count;
    char is_base_busy[2];
    int training_time;
} au;

void train(char fname[], long* g, char *t, au a[], int* u)
{
	int training_time;
	int unit_cost;
	int unit_stamina;
	char* phrase;

	/* is base busy training? */
	if (strcmp(a[0].is_base_busy, "0") != 0)
	{
		printf("Training in progress, cannot train new units");
	}
	
	/* initiate training */
	if (strcmp(a[0].is_base_busy, "0") == 0)
	{
		switch (*t)
		{
			case 'K':
				unit_cost = 400;
                unit_stamina = 70;
				training_time = 5;
				phrase = "training a knight";
				break;
			case 'S':
				unit_cost = 250;
                unit_stamina = 60;
				training_time = 3;
				phrase = "training a swordsman";
				break;
			case 'A':
				unit_cost = 250;
                unit_stamina = 40;
				training_time = 3;
				phrase = "training an archer";
				break;
			case 'P':
				unit_cost = 200;
                unit_stamina = 50;
				training_time = 3;
				phrase = "training a pikeman";
				break;
			case 'R':
				unit_cost = 500;
                unit_stamina = 90;
				training_time = 4;
				phrase = "producing a ram";
				break;
			case 'C':
				unit_cost = 800;
                unit_stamina = 50;
				training_time = 6;
				phrase = "producing a catapult";
				break;
			case 'W':
				unit_cost = 100;
                unit_stamina = 20;
				training_time = 2;
				phrase = "training a worker";
				break;
		}
		if (*g < unit_cost)
		{
			printf("Insufficient gold for %s!", phrase);
		}
		else if (*g >= unit_cost)
		{
			/* training start successful */
			strcpy(a[*u].affiliation, "P");
			strcpy(a[*u].unit_type, t);
			a[*u].unit_id = *u;
			a[*u].x_coord = 0;
			a[*u].y_coord = 0;
			a[*u].current_stamina = unit_stamina;
			a[*u].training_time = training_time;

			*g -= unit_cost;
			(*u)++;

			/* save order to rozkazy.txt */
			FILE *fptr; 
			fptr = fopen(fname, "a");
            if (!fptr)
			{
                printf("Cannot open rozkazy.txt");
            }

            if (fprintf(fptr, "0 B %c\n", *t) < 0)
			{
                fprintf(stderr, "\nUnable to write order to file.\n");
            }

            fclose(fptr);

			printf("Started %s. Gold left: %ld \n", phrase, *g);
			strcpy(a[0].is_base_busy, t);
		}
	}
}