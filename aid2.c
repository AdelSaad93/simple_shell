#include "main.h"

void handle_range(char **range, ssize_t read);
ssize_t get_new_length(char *range);
void logicalopreators(char *range, ssize_t *new_length);

/**
 * handle_range - Partitions a range read from standard input as needed.
 * @range: A pointer to a range read from standard input.
 * @read: The length of range.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_range(char **range, ssize_t read)
{
	char *old_range, *new_range;
	char previous, current, next;
	size_t i, j;
	ssize_t new_length;

	new_length = get_new_length(*range);
	if (new_length == read - 1)
		return;
	new_range = malloc(new_length + 1);
	if (!new_range)
		return;
	j = 0;
	old_range = *range;
	for (i = 0; old_range[i]; i++)
	{
		current = old_range[i];
		next = old_range[i + 1];
		if (i != 0)
		{
			previous = old_range[i - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new_range[j++] = ' ';
					new_range[j++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					new_range[j++] = ';';
					new_range[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					new_range[j++] = ' ';
				new_range[j++] = ';';
				if (next != ' ')
					new_range[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new_range[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new_range[j++] = '&';
					new_range[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new_range[j++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					new_range[j++] = '|';
					new_range[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && old_range[i - 1] != ' ')
				new_range[j++] = ' ';
			new_range[j++] = ';';
			if (next != ' ' && next != ';')
				new_range[j++] = ' ';
			continue;
		}
		new_range[j++] = old_range[i];
	}
	new_range[j] = '\0';

	free(*range);
	*range = new_range;
}

/**
 * get_new_length - Gets the new length of a range.
 * @range: The range to check.
 * Return: The new length of the range.
 * Description: Cuts short ranges containing '#' comments with '\0'.
 */

ssize_t get_new_length(char *range)
{
	size_t i;
	ssize_t new_length = 0;
	char current, next;

	for (i = 0; range[i]; i++)
	{
		current = range[i];
		next = range[i + 1];
		if (current == '#')
		{
			if (i == 0 || range[i - 1] == ' ')
			{
				range[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && range[i - 1] != ' ' && range[i - 1] != ';')
				{
					new_length += 2;
					continue;
				}
				else if (range[i - 1] == ';' && next != ' ')
				{
					new_length += 2;
					continue;
				}
				if (range[i - 1] != ' ')
					new_length++;
				if (next != ' ')
					new_length++;
			}
			else
				logicalopreators(&range[i], &new_length);
		}
		else if (current == ';')
		{
			if (i != 0 && range[i - 1] != ' ')
				new_length++;
			if (next != ' ' && next != ';')
				new_length++;
		}
		new_length++;
	}
	return (new_length);
}
/**
 * logicalopreators - Checks a range for logical operators "||" or "&&".
 * @range: A pointer to the character to check in the range.
 * @new_length: Pointer to new_length in get_new_length function.
 */
void logicalopreators(char *range, ssize_t *new_length)
{
	char previous, current, next;

	previous = *(range - 1);
	current = *range;
	next = *(range + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_length)++;
		else if (previous == '&' && next != ' ')
			(*new_length)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_length)++;
		else if (previous == '|' && next != ' ')
			(*new_length)++;
	}
}
