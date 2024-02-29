#include "main.h"

char *fault_enviro(char **myargs);
char *fault_1(char **myargs);
char *fault_2_exit(char **myargs);
char *fault_2_cd(char **myargs);
char *fault_2_syn(char **myargs);
/**
 * fault_enviro - Creates an fault message .
 * @myargs: An array of arguments passed to the command.
 * Return: The fault string.
 */

char *fault_enviro(char **myargs)
{
	char *fault, *histo_str;
	int length;

	histo_str = intostr(histo);
	if (!histo_str)
		return (NULL);

	myargs--;
	length = stringlength(name) + stringlength(histo_str) +
	stringlength(myargs[0]) + 45;
	fault = malloc(sizeof(char) * (length + 1));
	if (!fault)
	{
		free(histo_str);
		return (NULL);
	}

	stringcopy(fault, name);
	stringconcatenate(fault, ": ");
	stringconcatenate(fault, histo_str);
	stringconcatenate(fault, ": ");
	stringconcatenate(fault, myargs[0]);
	stringconcatenate(fault, ": Unable to add/remove from enviroironment\n");

	free(histo_str);
	return (fault);
}

/**
 * fault_1 - Creates an fault message.
 * @myargs: An array of arguments passed to the command.
 * Return: The fault string.
 */
char *fault_1(char **myargs)
{
	char *fault;
	int length;

	length = stringlength(name) + stringlength(myargs[0]) + 13;
	fault = malloc(sizeof(char) * (length + 1));
	if (!fault)
		return (NULL);

	stringcopy(fault, "name: ");
	stringconcatenate(fault, myargs[0]);
	stringconcatenate(fault, " not found\n");

	return (fault);
}

/**
 * fault_2_exit - Creates an fault message.
 * @myargs: An array of arguments passed to the command.
 * Return: The fault string.
 */
char *fault_2_exit(char **myargs)
{
	char *fault, *histo_str;
	int length;

	histo_str = intostr(histo);
	if (!histo_str)
		return (NULL);

	length = stringlength(name) + stringlength(histo_str) +
	stringlength(myargs[0]) + 27;
	fault = malloc(sizeof(char) * (length + 1));
	if (!fault)
	{
		free(histo_str);
		return (NULL);
	}

	stringcopy(fault, name);
	stringconcatenate(fault, ": ");
	stringconcatenate(fault, histo_str);
	stringconcatenate(fault, ": exit: Illegal number: ");
	stringconcatenate(fault, myargs[0]);
	stringconcatenate(fault, "\n");

	free(histo_str);
	return (fault);
}

/**
 * fault_2_cd - Creates an fault message for shellby_cd faults.
 * @myargs: An array of arguments passed to the command.
 *
 * Return: The fault string.
 */
char *fault_2_cd(char **myargs)
{
	char *fault, *histo_str;
	int length;

	histo_str = intostr(histo);
	if (!histo_str)
		return (NULL);

	if (myargs[0][0] == '-')
		myargs[0][2] = '\0';
	length = stringlength(name) + stringlength(histo_str) +
	stringlength(myargs[0]) + 24;
	fault = malloc(sizeof(char) * (length + 1));
	if (!fault)
	{
		free(histo_str);
		return (NULL);
	}

	stringcopy(fault, name);
	stringconcatenate(fault, ": ");
	stringconcatenate(fault, histo_str);
	if (myargs[0][0] == '-')
		stringconcatenate(fault, ": cd: Illegal option ");
	else
		stringconcatenate(fault, ": cd: can't cd to ");
	stringconcatenate(fault, myargs[0]);
	stringconcatenate(fault, "\n");

	free(histo_str);
	return (fault);
}

/**
 * fault_2_syn - Creates an fault message for syn faults.
 * @myargs: An array of arguments passed to the command.
 * Return: The fault string.
 */
char *fault_2_syn(char **myargs)
{
	char *fault, *histo_str;
	int length;

	histo_str = intostr(histo);
	if (!histo_str)
		return (NULL);

	length = stringlength(name) + stringlength(histo_str) +
	stringlength(myargs[0]) + 33;
	fault = malloc(sizeof(char) * (length + 1));
	if (!fault)
	{
		free(histo_str);
		return (NULL);
	}

	stringcopy(fault, name);
	stringconcatenate(fault, ": ");
	stringconcatenate(fault, histo_str);
	stringconcatenate(fault, ": syn fault: \"");
	stringconcatenate(fault, myargs[0]);
	stringconcatenate(fault, "\" unexpected\n");

	free(histo_str);
	return (fault);
}
