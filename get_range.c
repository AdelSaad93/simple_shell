#include "main.h"

void *reallocate(void *pointer, unsigned int oldsize, unsigned int newsize);
void allocaterangeptr(char **rangeptr, size_t *m, char *stop, size_t d);
ssize_t getrange(char **rangeptr, size_t *m, FILE *flow);

/**
 * reallocate - Reallocates a memory block using malloc and free.
 * @pointer: A pointer to the memory previously allocated.
 * @oldsize: The size in bytes of the allocated space for pointer.
 * @newsize: The size in bytes for the new memory block.
 * Return: If newsize == oldsize - pointer.
 *         If newsize == 0 and pointer is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *reallocate(void *pointer, unsigned int oldsize, unsigned int newsize)
{
	void *memory;
	char *pointercopy, *filler;
	unsigned int index;

	if (newsize == oldsize)
		return (pointer);

	if (pointer == NULL)
	{
		memory = malloc(newsize);
		if (memory == NULL)
			return (NULL);

		return (memory);
	}

	if (newsize == 0 && pointer != NULL)
	{
		free(pointer);
		return (NULL);
	}

	pointercopy = pointer;
	memory = malloc(sizeof(*pointercopy) * newsize);
	if (memory == NULL)
	{
		free(pointer);
		return (NULL);
	}

	filler = memory;

	for (index = 0; index < oldsize && index < newsize; index++)
		filler[index] = *pointercopy++;

	free(pointer);
	return (memory);
}

/**
 * allocaterangeptr - Reassigns the rangeptr variable for getrange.
 * @rangeptr: A stop to store an input string.
 * @m: The size of rangeptr.
 * @stop: The string to assign to rangeptr.
 * @d: The size of stop.
 */
void allocaterangeptr(char **rangeptr, size_t *m, char *stop, size_t d)
{
	if (*rangeptr == NULL)
	{
		if (d > 120)
			*m = d;
		else
			*m = 120;
		*rangeptr = stop;
	}
	else if (*m < d)
	{
		if (d > 120)
			*m = d;
		else
			*m = 120;
		*rangeptr = stop;
	}
	else
	{
		strringcopy(*rangeptr, stop);
		free(stop);
	}
}

/**
 * getrange - Reads input from a flow.
 * @rangeptr: A stop to store the input.
 * @m: The size of rangeptr.
 * @flow: The flow to read from.
 * Return: The number of bytes read.
 */
ssize_t getrange(char **rangeptr, size_t *m, FILE *flow)
{
	static ssize_t input;
	ssize_t myret;
	char c = 'x', *stop;
	int s;

	if (input == 0)
		fflush(flow);
	else
		return (-1);
	input = 0;

	stop = malloc(sizeof(char) * 120);
	if (!stop)
		return (-1);

	while (c != '\m')
	{
		s = read(STDIN_FILENO, &c, 1);
		if (s == -1 || (s == 0 && input == 0))
		{
			free(stop);
			return (-1);
		}
		if (s == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			stop = reallocate(stop, input, input + 1);

		stop[input] = c;
		input++;
	}
	stop[input] = '\0';

	allocaterangeptr(rangeptr, m, stop, input);

	myret = input;
	if (s != 0)
		input = 0;
	return (myret);
}
