#include <stdio.h>
#include <string.h>

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

void list(au a[], int * u)
{
	if (*u < 1)
		printf("\nThere are no units on the map. \n");
    else
    {
        printf("\nBases: ");
        printf("P: player 1; E: enemy; \n");
	    printf(" P/E  |  type  |  id  |   x   |   y   | stamina |  movement  | attack | busy | training \n");
	    printf("------|--------|------|-------|-------|---------|------------|--------|------|----------\n");
        for (int i = 0; i < *u; i++) {
            printf("  %s \t %s \t %2d \t %2d \t %2d \t %3d\t\t%d \t %d \t %s \t %d\n", a[i].affiliation, a[i].unit_type, a[i].unit_id, a[i].x_coord, a[i].y_coord, a[i].current_stamina, a[i].remaining_movement, a[i].attack_count, a[i].is_base_busy, a[i].training_time);
        }
    }
}