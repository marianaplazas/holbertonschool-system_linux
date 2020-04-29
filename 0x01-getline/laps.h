#ifndef LAPS_H
#define LAPS_H

#include <stdio.h>
#include <stdlib.h>

/**
 *@id: the unique identifier of the car
 *@laps: the number of laps in the race
 *@next: the pointer to the next node/car
 */
typedef struct cars
{
	int id;
	int laps;
	struct cars *next;
}car;
void free_list(car *list);
car *id_exists(car *head, int id);
void race_state(int *id, size_t size);
car *add_car(car **head, int id);
#endif
