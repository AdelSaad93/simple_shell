#include "main.h"

void free_myargs(char **myargs, char **forehead);
char *getproid(void);
char *get_enviro_value(char *start, int length);
void myvariable_replacement(char **myargs, int *exe_myret);

/**
 * free_myargs - Frees up memory taken by myargs.
 * @myargs: A null-terminated double pointer containing commands/arguments.
 * @forehead: A double pointer to the beginning of myargs.
 */
void free_myargs(char **myargs, char **forehead)
{
	size_t i;

	for (i = 0; myargs[i] || myargs[i + 1]; i++)
		free(myargs[i]);

	free(forehead);
}

/**
 * getproid - Gets the current process ID.
 * Description: Open stat file,a space delimited file containing information.
 * Return: The current process ID or NULL on failure.
 */
char *getproid(void)
{
	size_t i = 0;
	char *stream;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	stream = malloc(120);
	if (!stream)
	{
		close(file);
		return (NULL);
	}
	read(file, stream, 120);
	while (stream[i] != ' ')
		i++;
	stream[i] = '\0';

	close(file);
	return (stream);
}

/**
 * get_enviro_value - Gets value corresponding to an enviroironmental variable.
 * @start: The enviroironmental variable to search for.
 * @length: The lengthgth of the enviroironmental variable to search for.
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the enviroironmental variable.
 * Description: variables are stored in the format VARIABLE=VALUE.
 */
char *get_enviro_value(char *start, int length)
{
	char **myvar_addr;
	char *replacement = NULL, *tempo, *myvar;

	myvar = malloc(length + 1);
	if (!myvar)
		return (NULL);
	myvar[0] = '\0';
	stringnconcatenate(myvar, start, length);

	myvar_addr = getenviro(myvar);
	free(myvar);
	if (myvar_addr)
	{
		tempo = *myvar_addr;
		while (*tempo != '=')
			tempo++;
		tempo++;
		replacement = malloc(stringlength(tempo) + 1);
		if (replacement)
			stringcopy(replacement, tempo);
	}

	return (replacement);
}

/**
 * myvariable_replacement - Handles variable replacement.
 * @range: A double pointer containing the command and arguments.
 * @exe_myret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 */
void myvariable_replacement(char **range, int *exe_myret)
{
	int j, k = 0, length;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *range;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = getproid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = intostr(*exe_myret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				length = k - (j + 1);
				replacement = get_enviro_value(&old_line[j + 1], length);
			}
			new_line = malloc(j + stringlength(replacement)
					  + stringlength(&old_line[k]) + 1);
			if (!range)
				return;
			new_line[0] = '\0';
			stringnconcatenate(new_line, old_line, j);
			if (replacement)
			{
				stringconcatenate(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			stringconcatenate(new_line, &old_line[k]);
			free(old_line);
			*range = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}

