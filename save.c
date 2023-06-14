#include <stdio.h>

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

void save(long* g, int* u, au a[])
{
    FILE *f = fopen("player1.txt", "w");
    if (!f)
    {
        fprintf(stderr, "unable to open file for writing\n");
        return;
    }

    /* Are units being trained? */
    int unit_in_training;
	for (int i = 0; i < *u; i++)
    {
        if (a[i].training_time > 0)
            unit_in_training = i;
        else
            unit_in_training = 0;
    }
        
    if (unit_in_training != 0)
    {
        if ((fprintf(f, "%s %s %d 0 0 %d %d\n", a[unit_in_training].affiliation, a[unit_in_training].unit_type, a[unit_in_training].unit_id, a[unit_in_training].current_stamina, --a[unit_in_training].training_time) < 0))
                fprintf(stderr, "unable to write training units\n");
    }
    else
    { 
		if (fprintf(f, "0 0 0 0 0 0 0\n") < 0)
            fprintf(stderr, "unable to write training units\n");
    }
    
    /* Save the amount of gold */
	if (fprintf(f, "%ld\n", *g) < 0)
    {
        fprintf(stderr, "unable to write bank status\n");
    }

    /* Save the base condition */
    for (int i = 0; i < 2; i++)
    {
        if (fprintf(f, "%s %s %d %d %d %d %s\n", a[i].affiliation, a[i].unit_type, a[i].unit_id, a[i].x_coord, a[i].y_coord, a[i].current_stamina, a[i].is_base_busy) < 0)
        {
            fprintf(stderr, "unable to write base condition\n");
        }
    }
    
    /* Save active units */
    if (*u == 0)
    {
        fclose(f);
    }
    else if (unit_in_training != 0)
    {
        for (int i = 2; i < *u - 1; i++)
        {
            if (fprintf(f, "%s %s %d %d %d %d\n", a[i].affiliation, a[i].unit_type, a[i].unit_id, a[i].x_coord, a[i].y_coord, a[i].current_stamina) < 0)
            {
                fprintf(stderr, "unable to write active units\n");
            }    
        }
    }
    else if (*u > 0)
    {
        for (int i = 2; i < *u; i++)
        {
            if (fprintf(f, "%s %s %d %d %d %d\n", a[i].affiliation, a[i].unit_type, a[i].unit_id, a[i].x_coord, a[i].y_coord, a[i].current_stamina) < 0)
            {
                fprintf(stderr, "unable to write active units\n");
            }    
        }
    }

    fclose(f);
}