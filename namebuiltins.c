#include "main.h"

int simpleshell_name(char **myargs, char  **forehead);
void set_name(char *myvarname, char *value);
void print_name(name_t *name);

/**
 * simpleshell_name - Builtin command that either prints all names.
 * @myargs: An array of arguments.
 * @forehead: A double pointer to the beginning of myargs.
 * Return: If an fault occurs -1 Otherwise 0.
 */
int simpleshell_name(char **myargs, char  **forehead)
{
	name_t *tempo = names;
	int i, myret = 0;

	char *value;

	if (!myargs[0])
	{
		while (tempo)
		{
			print_name(tempo);
			tempo = tempo->next;
		}
		return (myret);
	}
	for (i = 0; myargs[i]; i++)
	{
		tempo = names;
		value = stringcharacter(myargs[i], '=');
		if (!value)
		{
			while (tempo)
			{
				if (stringcompare(myargs[i], tempo->name) == 0)
				{
					print_name(tempo);
					break;
				}
				tempo = tempo->next;
			}
			if (!tempo)
				myret = create_fault(myargs + i, 1);
		}
		else
			set_name(myargs[i], value);
	}
	return (myret);
}

/**
 * set_name - Will either set an existing name 'name' with a new value,
 * @**myvarname: Name of the name.
 * @value: value of the name. First character is a '='.
 */
void set_name(char *myvarname, char *value)
{
	name_t *tempo = names;
	int length, a, b;
	char *value;

	*value = '\0';
	value++;
	length = stringlength(value) - stringsubstring(value, "'\"");
	value = malloc(sizeof(char) * (length + 1));
	if (!value)
		return;
	for (a = 0, b = 0; value[a]; a++)
	{
		if (value[a] != '\'' && value[a] != '"')
			value[b++] = value[a];
	}
	value[b] = '\0';
	while (tempo)
	{
		if (stringcompare(myvarname, tempo->name) == 0)
		{
			free(tempo->value);
			tempo->value = value;
			break;
		}
		tempo = tempo->next;
	}
	if (!tempo)
		add_name_end(&names, myvarname, value);
}

/**
 * print_name - Prints the name in the format name='value'.
 * @name: Pointer to an name.
 */
void print_name(name_t *name)
{
	char *name_string;
	int length = stringlength(name->name) + stringlength(name->value) + 4;

	name_string = malloc(sizeof(char) * (length + 1));
	if (!name_string)
		return;
	stringcopy(name_string, name->name);
	stringconcatenate(name_string, "='");
	stringconcatenate(name_string, name->value);
	stringconcatenate(name_string, "'\n");

	write(STDOUT_FILENO, name_string, length);
	free(name_string);
}
/**
 * replace_names - Goes through the arguments and replace any matching name
 * with their value.
 * @myargs: pointer to the arguments.
 *
 * Return: pointer to the arguments.
 */
char **replace_names(char **myargs)
{
	name_t *tempo;
	int i;
	char **mynewvalue;

	if (stringcompare(myargs[0], "name") == 0)
		return (myargs);
	for (i = 0; myargs[i]; i++)
	{
		tempo = names;
		while (tempo)
		{
			if (stringcompare(myargs[i], tempo->name) == 0)
			{
				mynewvalue = malloc(sizeof(char) * (stringlength(tempo->value) + 1));
				if (!mynewvalue)
				{
					free_myargs(myargs, myargs);
					return (NULL);
				}
				stringcopy(mynewvalue, tempo->value);
				free(myargs[i]);
				myargs[i] = mynewvalue;
				i--;
				break;
			}
			tempo = tempo->next;
		}
	}

	return (myargs);
}

