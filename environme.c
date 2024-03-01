#include "main.h"

char **copyenviro(void);
void free_enviro(void);
char **get_enviro(const char *myvar);

/**
 * copyenviro - Creates a copy of the environment.
 * Return: If an error occurs - NULL.
 * otherwise - a double pointer to the new copy.
 */
char **copyenviro(void)
{
	char **new_environme;
	size_t size;
	int list;

	for (size = 0; environme[size]; size++)
		;

	new_environme = malloc(sizeof(char *) * (size + 1));
	if (!new_environme)
		return (NULL);

	for (list = 0; environme[list]; list++)
	{
		new_environme[list] = malloc(stringlength(environme[list]) + 1);

		if (!new_environme[list])
		{
			for (list--; list >= 0; list--)
				free(new_environme[list]);
			free(new_environme);
			return (NULL);
		}
		stringcopy(new_environme[list], environme[list]);
	}
	new_environme[list] = NULL;

	return (new_environme);
}

/**
 * free_enviro - Frees the the environment copy.
 */
void free_enviro(void)
{
	int list;

	for (list = 0; environme[list]; list++)
		free(environme[list]);
	free(environme);
}

/**
 * get_enviro - Gets an environmental myvariable from the PATH.
 * @myvar: The name of the environmental myvariable to get.
 * Return: If the environmental myvariable does not exist - NULL.
 *  Otherwise - a pointer to the environmental myvariable.
 */
char **get_enviro(const char *myvar)
{
	int list, length;

	length = stringlength(myvar);
	for (list = 0; environme[list]; list++)
	{
		if (stringncompare(myvar, environme[list], length) == 0)
			return (&environme[list]);
	}

	return (NULL);
}

