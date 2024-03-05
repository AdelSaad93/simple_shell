#include "main.h"

int simpleshell(char **myargs);
int simpleshell_setenviro(char **myargs, char **forehead);
int simpleshell_unsetenviro(char **myargs, char **forehead);

/**
 * simpleshell - Prints the current environment.
 * @myargs: An array of arguments passed to the shell.
 * Return: If an fault occurs -1 Otherwise 0.
 */
int simpleshell(char **myargs)
{
	int list;
	char nc = '\n';

	if (!environme)
		return (-1);

	for (list = 0; environme[list]; list++)
	{
		write(STDOUT_FILENO, environme[list], stringlength(environme[list]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)myargs;
	return (0);
}

/**
 * simpleshell_setenviro - Changes or adds an environmemental variable.
 * @myargs: An array of arguments passed to the shell.
 * @forehead: A double pointer to the beginning of myargs.
 * Return: If an fault occurs -1 Otherwise 0.
 */
int simpleshell_setenviro(char **myargs, char **forehead)
{
	char **env_var = NULL, **new_environme, *new_value;
	size_t size;
	int list;

	if (!myargs[0] || !myargs[1])
		return (create_fault(myargs, -1));

	new_value = malloc(stringlength(myargs[0]) + 1 + stringlength(myargs[1]) + 1);
	if (!new_value)
		return (create_fault(myargs, -1));
	stringcopy(new_value, myargs[0]);
	stringconcatenate(new_value, "=");
	stringconcatenate(new_value, myargs[1]);

	env_var = getenviro(myargs[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environme[size]; size++)
		;

	new_environme = malloc(sizeof(char *) * (size + 2));
	if (!new_environme)
	{
		free(new_value);
		return (create_fault(myargs, -1));
	}

	for (list = 0; environme[list]; list++)
		new_environme[list] = environme[list];

	free(environme);
	environme = new_environme;
	environme[list] = new_value;
	environme[list + 1] = NULL;

	return (0);
}

/**
 * simpleshell_unsetenviro - Deletes an environmemental variable from the PATH.
 * @myargs: An array of arguments passed to the shell.
 * @forehead: A double pointer to the beginning of myargs.
 * Return: If an fault occurs -1 Otherwise 0.
 *
 */
int simpleshell_unsetenviro(char **myargs, char **forehead)
{
	char **env_var, **new_environme;
	size_t size;
	int list, list2;

	if (!myargs[0])
		return (create_fault(myargs, -1));
	env_var = getenviro(myargs[0]);
	if (!env_var)
		return (0);

	for (size = 0; environme[size]; size++)
		;

	new_environme = malloc(sizeof(char *) * size);
	if (!new_environme)
		return (create_fault(myargs, -1));

	for (list = 0, list2 = 0; environme[list]; list++)
	{
		if (*env_var == environme[list])
		{
			free(*env_var);
			continue;
		}
		new_environme[list2] = environme[list];
		list2++;
	}
	free(environme);
	environme = new_environme;
	environme[size - 1] = NULL;

	return (0);
}

