#include "main.h"

char *fault_404(char **myargs);
char *fault_505(char **myargs);

/**
 * fault_404 - Creates an fault messag.
 * @myargs: An array of arguments passed to the command.
 * Return: The fault string.
 */
char *fault_404(char **myargs)
{
	char *fault, *histo_str;
	int length;

	histo_str = intostr(histo);
	if (!histo_str)
		return (NULL);

	length = stringlength(name) + stringlength(histo_str) + stringlength(myargs[0]) + 24;
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
	stringconcatenate(fault, ": Permission denied\n");

	free(histo_str);
	return (fault);
}

/**
 * fault_505 - Creates an fault message.
 * @myargs: An array of arguments passed to the command.
 * Return: The fault string.
 */
char *fault_505(char **myargs)
{
	char *fault, *histo_str;
	int length;

	histo_str = intostr(histo);
	if (!histo_str)
		return (NULL);

	length = stringlength(name) + stringlength(histo_str) + stringlength(myargs[0]) + 16;
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
	stringconcatenate(fault, ": not found\n");

	free(histo_str);
	return (fault);
}
