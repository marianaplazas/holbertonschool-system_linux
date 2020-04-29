#include "laps.h"
car *id_exist(car *head, int id)
{
	while (head != NULL)
	{
		if (head->id == id)
			return (head);
		head = head->next;
	}
	return (NULL);
}
/**
 *
 */
car *add_car(car **head, int id)
{
	car *current = NULL;
	car *new = NULL;

	if (!head)
		return (NULL);

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->id = id;
	new->laps = 0;
	new->next = NULL;
	printf("Car %d joined the race\n", new->id);

	if (!*head)
		return (new);

	current = (*head);
	if (id < current->id)
	{
		new->next = *head;
		*head = new;
	}
	else
	{
		while (current->next && current->next->id < id)
			current = current->next;

		new->next = current->next;
		current->next = new;
	}
	return (*head);
}

/**
 *
 */
void free_list(car *list)
{
	car *tmp;

	while (cars != NULL)
	{
		tmp = cars;
		cars = cars->next;
		free(tmp);
	}
}
/**
 *
 */
void race_state(int *id, size_t size)
{
	static car *cars;
	car *check;
	size_t i = 0;

	if (size == 0)
	{
		free_list(cars);
		return;
	}

	if (cars == NULL)
	{
		cars = add_car(&car, id[0]);
		cars->laps--;
	}
	for (i = 0; i < size; i++)
	{
		check = id_exists(car, id[i]);
		if (!check)
			insert_car(&car, id[i]);
		else
			check->laps++;
	}
	printf("Race state:\n");
	for (node = head; node; node = node->next)
		printf("Car %d [%lu laps]\n", node->id, node->laps);
}
