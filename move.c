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

void move(char fname[], au a[], int* u, int m[][MAP_SIZE_X]) {
    
    int allowed_movement; // unit's movement points
    int id_counter; // validates the id indicated by the user
    int coord_counter; // monitors if two coordinates were given
    int map_field_occupied = 0; //are there enemy units on the specified field?
    int distance; // the distance the user attempts to move the unit
    int id; // the requested unit id
    int x; // target x coordinate
    int y; // target y coordinate
    char* unit; // unit type retrieved from active_units    

    id_counter = 0;
    if (*u <= 2) {
        printf("\nThere are no units capable of moving.\n");
        printf("Type MENU to go back to main menu.\n");
    } else {
        /* Requesting user input: indicating the unit to be moved */
        while (id_counter < 1) {
            printf("Which unit do you intend to move? (ID): ");
            if (scanf(" %d", &id) == 1 && (id >= 2 && id <= *u-1))
                id_counter++;
            else {
                printf("\n Unit ID needs to range from 2 to %d. \n", *u-1);
                continue;
            }
        }
    }

    coord_counter = 0; 
    if (id_counter > 0) {
        if (strcmp(a[id].affiliation, "E") == 0) {
        
            printf("\nCannot select enemy units.\n");
            printf("Type MENU to go back to main menu.\n");
        
        } else if ((strcmp(a[id].affiliation, "P") == 0) && (a[id].training_time > 0)) {
        
            printf("\nCannot move units undergoing training.\n");
            printf("Type MENU to go back to main menu.\n");
        
        } else {
        
            while (coord_counter < 2) {    
            /* requesting target coordinates and validating input*/
            printf("Please specify the target X coordinate: ");
                if (scanf(" %d", &x) == 1 && (x >= 0 && x <= MAP_SIZE_X - 1)) {
                    coord_counter++;
                    //printf("\nCoord counter: %d\n", coord_counter);    
                } else {
                    printf("\nX coordinate needs to range from 0 to %d.\n", MAP_SIZE_X - 1);
                    continue;
                }
            printf("Please specify the target Y coordinate: ");
                if (scanf(" %d", &y) == 1 && (y >= 0 && y <= MAP_SIZE_Y - 1)) {
                    coord_counter++;
                    //printf("\nCoord counter: %d\n", coord_counter);
                } else {
                    printf("\nY coordinate needs to range from 0 to %d.\n", MAP_SIZE_Y - 1);
                    continue;
                }
            }
        }    
    }

        /* prevent the unit from going on obstacles */
    if (coord_counter >= 2) {
        if (m[y][x] == 9) {

            printf("\nThis field is a natural obstacle.\n");
            printf("Type MENU to go back to main menu.\n");
            map_field_occupied = 1;
        
        } else if (m[y][x] == 2) {
        
        /* prevent the unit from going on an enemy-occupied field  */
            printf("\nThis field is an enemy base.\n");
            map_field_occupied = 1;
        
        } else if (m[y][x] == 0) {
    
            for (int i = 0; i < *u; i++)
		        if ((strcmp(a[i].affiliation, "E") == 0) && (a[i].x_coord == x) && (a[i].y_coord == y)) {
    	            map_field_occupied = 1;
                }
    
            if (map_field_occupied == 1) {
                printf("\nThis is enemy-held territory.\n\n");
                printf("Type MENU to go back to main menu.\n");
            }
        }
    }

        /* validating the distance a unit may travel*/
        if (map_field_occupied < 1) {

            distance = abs(a[id].x_coord - x) + abs(a[id].y_coord - y);

            if (strcmp(a[id].unit_type, "K") == 0)
                allowed_movement = 5;
            else
                allowed_movement = 2;
            
            if ((distance > a[id].remaining_movement) || (distance > allowed_movement)) {
                printf("Distance exceeds the unit's range.\n");
                printf("Type MENU to go back to main menu.\n");
            } else if ((distance <= allowed_movement) && (distance <= a[id].remaining_movement)) {
                a[id].remaining_movement = allowed_movement - distance;
                printf("Ordering unit %d to move to X: %d, Y: %d.\n", id, x, y);

                /* order successful, write to file */
                FILE *fptr;

                fptr = fopen(fname, "a");
                if (!fptr) {
                    printf("Cannot open rozkazy.txt");
                }

                if (fprintf(fptr, "%d M %d %d\n", id, x, y) < 0) {
                    fprintf(stderr, "\nUnable to write order to file.\n");
                }

                fclose(fptr);

                printf("Type MENU to go back to main menu.\n");
            } 
        }
    }
