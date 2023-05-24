#include <stdio.h>
#include <stdlib.h>

#define MAP_SIZE_X 32
#define MAP_SIZE_Y 5

void map(char fname[], int m[][MAP_SIZE_X], int t[][MAP_SIZE_X+1])
{
    FILE * fptr;
 
    char map_field;

    fptr = fopen(fname, "r"); 
    
    map_field = fgetc(fptr);

    for (int i = 0; i < MAP_SIZE_Y; i++)
        for (int j = 0; j < MAP_SIZE_X+1; j++)
        {
            t[i][j] = map_field - '0'; //char symbol value to int conversion by subtracting 38 (ASCII code for '0')
            map_field = fgetc(fptr);
        }

    for (int i = 0; i < MAP_SIZE_Y; i++)
        for (int j = 0; j < MAP_SIZE_X; j++)
            m[i][j] = t[i][j];

    fclose (fptr);
}