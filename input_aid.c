#include "main.h"

char *get_myargs(char *range, int *exe_myret);
int call_myargs(char **myargs, char **forehead, int *exe_myret);
int run_myargs(char **myargs, char **forehead, int *exe_myret);
int handle_myargs(int *exe_myret);
int check_myargs(char **myargs);

/**
 * get_myargs - Gets a command from standard input.
 * @range: A buffer to store the command.
 * @exe_myret: The return value of the last executed command.
 * Return: If an fault occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_myargs(char *range, int *exe_myret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (range)
		free(range);

	read = _getrange(&range, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		histo++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_myargs(range, exe_myret));
	}

	range[read - 1] = '\0';
	variable_replacement(&range, exe_myret);
	handle_range(&range, read);

	return (range);
}

/**
 * call_myargs - Partitions operators from commands and calls them.
 * @myargs: An array of arguments.
 * @forehead: A double pointer to the beginning of myargs.
 * @exe_myret: The return value of the parent process' last executed command.
 * Return: The return value of the last executed command.
 */
int call_myargs(char **myargs, char **forehead, int *exe_myret)
{
	int myret, index;

	if (!myargs[0])
		return (*exe_myret);
	for (index = 0; myargs[index]; index++)
	{
		if (_strncmp(myargs[index], "||", 2) == 0)
		{
			free(myargs[index]);
			myargs[index] = NULL;
			myargs = replace_aliases(myargs);
			myret = run_myargs(myargs, forehead, exe_myret);
			if (*exe_myret != 0)
			{
				myargs = &myargs[++index];
				index = 0;
			}
			else
			{
				for (index++; myargs[index]; index++)
					free(myargs[index]);
				return (myret);
			}
		}
		else if (_strncmp(myargs[index], "&&", 2) == 0)
		{
			free(myargs[index]);
			myargs[index] = NULL;
			myargs = replace_aliases(myargs);
			myret = run_myargs(myargs, forehead, exe_myret);
			if (*exe_myret == 0)
			{
				myargs = &myargs[++index];
				index = 0;
			}
			else
			{
				for (index++; myargs[index]; index++)
					free(myargs[index]);
				return (myret);
			}
		}
	}
	myargs = replace_aliases(myargs);
	myret = run_myargs(myargs, forehead, exe_myret);
	return (myret);
}

/**
 * run_myargs - Calls the execution of a command.
 * @myargs: An array of arguments.
 * @forehead: A double pointer to the beginning of myargs.
 * @exe_myret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_myargs(char **myargs, char **forehead, int *exe_myret)
{
	int myret, i;
	int (*builtin)(char **myargs, char **forehead);

	builtin = get_builtin(myargs[0]);

	if (builtin)
	{
		myret = builtin(myargs + 1, forehead);
		if (myret != EXIT)
			*exe_myret = myret;
	}
	else
	{
		*exe_myret = execute(myargs, forehead);
		myret = *exe_myret;
	}

	histo++;

	for (i = 0; myargs[i]; i++)
		free(myargs[i]);

	return (myret);
}

/**
 * handle_myargs - Gets, calls, and runs the execution of a command.
 * @exe_myret: The return value of the parent process' last executed command.
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_myargs(int *exe_myret)
{
	int myret = 0, index;
	char **myargs, *range = NULL, **forehead;

	range = get_myargs(range, exe_myret);
	if (!range)
		return (END_OF_FILE);

	myargs = _strtok(range, " ");
	free(range);
	if (!myargs)
		return (myret);
	if (check_myargs(myargs) != 0)
	{
		*exe_myret = 2;
		free_myargs(myargs, myargs);
		return (*exe_myret);
	}
	forehead = myargs;

	for (index = 0; myargs[index]; index++)
	{
		if (_strncmp(myargs[index], ";", 1) == 0)
		{
			free(myargs[index]);
			myargs[index] = NULL;
			myret = call_myargs(myargs, forehead, exe_myret);
			myargs = &myargs[++index];
			index = 0;
		}
	}
	if (myargs)
		myret = call_myargs(myargs, forehead, exe_myret);

	free(forehead);
	return (myret);
}

/**
 * check_myargs - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @myargs: 2D pointer to tokenized commands and arguments.
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_myargs(char **myargs)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; myargs[i]; i++)
	{
		cur = myargs[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_fault(&myargs[i], 2));
			nex = myargs[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_fault(&myargs[i + 1], 2));
		}
	}
	return (0);
}
