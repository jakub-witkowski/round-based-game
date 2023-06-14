#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void attack(char fname[], au a[], int* u)
{
    int allowed_movement; // unit's movement points
    int attacker_id_counter; // validates the id indicated by the user
    int target_id_counter; // validates the target id indicated by the user
    int attacker_id; // the requested attacking unit id
    int target_id; // the requested target unit id
    int target_coord_counter = 0; // used for validating whether target coordinates have been established
    int distance; // the distance between the attacker unit and the target unit
    int input;

    /* Requesting user input: indicating the attacking unit */
    attacker_id_counter = 0;
    if (*u < 2)
    {
        printf("\nThere are no units capable of making an attack.\n");
        printf("Type MENU to go back to main menu.\n");
    }
    else
    {
        if (attacker_id_counter < 1)
        {
            printf("Select the unit for attacking the enemy (ID): ");
            while ((input = scanf("%d", &attacker_id)) == 0)
            {
                scanf("%*[^\n]");
                printf("\n Unit ID needs to range from 2 to %d. Enter unit ID: \n", *u - 1);
            }
            if (input == EOF)
            {
                printf("Nothing more to read - and no number found\n");
            }
            else
            {
                attacker_id_counter++;
            }
        }
    }

    /* Validating user input */
    if (attacker_id_counter > 0)
    {
        if ((a[attacker_id].training_time > 0) && (strcmp(a[attacker_id].affiliation, "P") == 0))
        {
            printf("\nCannot select units undergoing training.\n");
            printf("Type MENU to go back to main menu.\n");
            target_id_counter = -1;
        }
        else if (a[attacker_id].attack_count == 0)
        {
            printf("\nAttack limit per round exceeded.\n");
            printf("\nType MENU to go back to main menu.\n");
            target_id_counter = -1;
        }
        else if (strcmp(a[attacker_id].affiliation, "E") == 0)
        {
            printf("\nCannot select enemy units.\n");
            printf("Type MENU to go back to main menu.\n");
            target_id_counter = -1;
        }
        else
        {
            /* Requesting user input: indicating the target unit */
            target_id_counter = 0;
            while (target_id_counter < 1)
            {
                printf("Which enemy unit do you intend to attack? (ID): ");
                if (scanf(" %d", &target_id) == 1 && (target_id > 0 && target_id <= *u - 1))
                {
                    fflush(stdin);
                    target_id_counter++;
                }
                else
                {
                    printf("\n Unit ID needs to range from 1 to %d.\n", *u - 1);
                    continue;
                }
            }
        }
    }    

    if (target_id_counter > 0)
    {
        if (strcmp(a[target_id].affiliation, "P") == 0)
        {
            printf("\nCannot attack friendly units.\n");
            printf("Type MENU to go back to main menu.\n");
        }
        else
        {    
            /* validating if the enemy unit is within the attacking unit range */
            distance = abs(a[attacker_id].x_coord - a[target_id].x_coord) + abs(a[attacker_id].y_coord - a[target_id].y_coord);
    
            if (strcmp(a[attacker_id].unit_type, "K") == 0)
                allowed_movement = 5;
            else
                allowed_movement = 2;
     
            if ((distance > a[attacker_id].remaining_movement + 1) || (distance > allowed_movement))
            {
                printf("\nTarget unit outside the attacking unit range.\n");
                printf("\nType MENU to go back to main menu.\n");
            }
            else if ((distance < allowed_movement) && (distance < a[attacker_id].remaining_movement))
            {
                a[attacker_id].remaining_movement = allowed_movement - distance;
                printf("\nOrdering unit %d to attack enemy unit %d.\n", attacker_id, target_id);
                a[attacker_id].attack_count = 0;

                /* order successful, write to file */
                FILE *fptr; 
                fptr = fopen(fname, "a");
                if (!fptr)
                {
                    printf("Cannot open rozkazy.txt");
                }

                if (fprintf(fptr, "%d A %d\n", attacker_id, target_id) < 0)
                {
                    fprintf(stderr, "\nUnable to write order to file.\n");
                }

                fclose(fptr);

                printf("\nType MENU to go back to main menu.\n");
            } 
        }
    }
}

