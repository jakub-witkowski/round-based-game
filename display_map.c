#include <stdio.h>
#include <stdlib.h>

#define MAP_SIZE_X 32
#define MAP_SIZE_Y 5

void display_map(int m[][MAP_SIZE_X])
{
/* displaying the map with coordinate grid */
    printf("\n y\\x");
    for (int i = 0; i < MAP_SIZE_X; i++)
        if (i < 10)
            printf(" %d ", i);
        else
            printf(" %d", i);
    printf("\n");
    printf("--+-------------------------------------------------------------------------------------------------");

    printf("\n");
    for (int i = 0; i < MAP_SIZE_Y; i++)
    {
        printf("%d | ", i);
        for (int j = 0; j < MAP_SIZE_X; j++)
        if (j == 31)
                printf(" %d \n", m[i][j]);
        else
                printf(" %d ", m[i][j]);
    }
    printf("\n");
    printf("Key: 0: open area; 1: your base; 2: enemy base; 6: gold mine; 9: obstacle.");
    printf("\n\n");
}