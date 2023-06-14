#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE_X 32
#define MAP_SIZE_Y 5

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

void move(char fname[], au a[], int* u, int m[][MAP_SIZE_X])
{   
    int allowed_movement; // unit's movement points
    int id_counter = 0; // validates the id indicated by the user
    int coord_counter = 0; // monitors if two coordinates were given
    //int map_field_occupied = 0; //are there enemy units on the specified field?
    int distance; // the distance the user attempts to move the unit
    int id; // the requested unit id
    int x; // target x coordinate
    int y; // target y coordinate
    char* unit; // unit type retrieved from active_units
    int input; // auxiliary variable making sure scanf() doesn't fall into an infinite loop;
    int stop = 0; // 0 = validation continues; 1 = stops the validation process;  

    if (*u < 2)
    {
        printf("\nThere are no units capable of moving.\n");
        printf("Type MENU to go back to main menu.\n");
    }
    else if (*u >= 2)
    {
        /* Requesting user input: indicating the unit to be moved */
        printf("Which unit do you intend to move? (ID): ");
        while ((input = scanf("%d", &id)) == 0)
        {
            scanf("%*[^\n]");
            printf("\n Unit ID needs to range from 2 to %d. Enter unit ID: \n", *u - 1);
        }
        if (input == EOF)
        {
            printf("Nothing to read and no number found\n");
        }
        else
        {
            id_counter++;
        }
    }

    /* Validating user input: unit ID */
    if (id_counter > 0)
    {
        if (id > *u - 1)
        {
            printf("\n Unit ID needs to range from 2 to %d. \n", *u - 1);
            printf("Type MENU to go back to main menu.\n");
            stop = 1;
        }
        if ((stop == 0) && (id == 0))
        {
            printf("\nThe base cannot move.\n");
            printf("Type MENU to go back to main menu.\n");
            stop = 1;
        }
        if ((stop == 0) && (strcmp(a[id].affiliation, "E") == 0))
        {
            printf("\nCannot select enemy units.\n");
            printf("Type MENU to go back to main menu.\n");
            stop = 1;
        }
        if ((stop == 0) && ((strcmp(a[id].affiliation, "P") == 0) && (a[id].training_time > 0)))
        {
            printf("\nCannot move units undergoing training.\n");
            printf("Type MENU to go back to main menu.\n");
            stop = 1;
        }
    }
    
    if ((stop == 0) && (id_counter > 0))
    {
        printf("Selected unit: %d (%s), current position: X: %d, Y: %d \n", a[id].unit_id, a[id].unit_type, a[id].x_coord, a[id].y_coord);
    }

    if ((stop == 0) && (id_counter > 0))
    {    
        /* requesting target coordinates and validating input*/
        printf("Please specify the target X coordinate: ");
        while ((input = scanf("%d", &x)) == 0)
        {
            scanf("%*[^\n]");
            printf("\nX coordinate needs to range from 0 to %d.\n", MAP_SIZE_X - 1);
        }
        if (input == EOF)
        {
            printf("Nothing to read and no number found\n");
        }
        else
        {
            coord_counter++;
        }
    }

    if ((stop == 0) && (coord_counter == 1))
    {
        if (x < 0 || x > MAP_SIZE_X - 1)
        {
            /* Is X within range? */
            printf("\nX coordinate needs to range from 0 to %d.\n", MAP_SIZE_X - 1);
            printf("Type MENU to go back to main menu.\n");
            stop = 1;
        }
        else
            stop = 0;
    }

    if ((stop == 0) && (coord_counter == 1))
    {        
        printf("Please specify the target Y coordinate: ");
        while ((input = scanf("%d", &y)) == 0)
        {
            scanf("%*[^\n]");
            printf("\nY coordinate needs to range from 0 to %d.\n", MAP_SIZE_Y - 1);
        }    
        if (input == EOF)
        {
            printf("Nothing to read and no number found\n");
        }
        else
        {
            coord_counter++;
        }
    }
     

    /* Validating user input: target coordinates */
    if (coord_counter == 2)
    {
        if ((stop == 0) && (y < 0 || y > MAP_SIZE_Y - 1))
        {
            /* Is Y within range? */
            printf("\nY coordinate needs to range from 0 to %d.\n", MAP_SIZE_Y - 1);
            printf("Type MENU to go back to main menu.\n");
            stop = 1;
        }
        if ((stop == 0) && (m[y][x] == 9))
        {
            /* prevent the unit from going on obstacles */
            printf("\nThis field is a natural obstacle.\n");
            printf("Type MENU to go back to main menu.\n");
            stop = 1;
        }
        if ((stop == 0) && (m[y][x] == 2))
        {
            /* prevent the unit from going on an enemy-occupied field  */
            printf("\nThis field is an enemy base.\n");
            printf("Type MENU to go back to main menu.\n");
            stop = 1;
        }
        if ((stop == 0) && (m[y][x] == 0))
        {
            for (int i = 0; i < *u; i++)
		        if ((strcmp(a[i].affiliation, "E") == 0) && (a[i].x_coord == x) && (a[i].y_coord == y))
                {
                    printf("\nThis is enemy-held territory.\n\n");
                    printf("Type MENU to go back to main menu.\n");
                    stop = 1;
                }
        }
    }

    /* validating the distance a unit may travel*/
    if ((stop == 0) && (coord_counter == 2))
    {
        distance = abs(a[id].x_coord - x) + abs(a[id].y_coord - y);

        if (strcmp(a[id].unit_type, "K") == 0)
            allowed_movement = 5;
        else
            allowed_movement = 2;
            
        if ((distance > a[id].remaining_movement) || (distance > allowed_movement))
        {
            printf("Distance exceeds the unit's range.\n");
            printf("Type MENU to go back to main menu.\n");
        }
        else if ((distance <= allowed_movement) && (distance <= a[id].remaining_movement))
        {
            a[id].remaining_movement = allowed_movement - distance;
            printf("Ordering unit %d to move to X: %d, Y: %d.\n", id, x, y);

            /* order successful, write to file */
            FILE *fptr;

            fptr = fopen(fname, "a");
            if (!fptr)
            {
                printf("Cannot open rozkazy.txt");
            }

            if (fprintf(fptr, "%d M %d %d\n", id, x, y) < 0)
            {
                fprintf(stderr, "\nUnable to write order to file.\n");
            }

            fclose(fptr);

            printf("Type MENU to go back to main menu.\n");
        } 
    }
}