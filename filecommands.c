#include "main.h"

int cannotopen(char *file_path);
int filecommands(char *file_path, int *exe_myret);

/**
 * cannotopen - If the file doesn't exist or lacks proper permissions, print
 * a cant open fault.
 * @file_path: Path to the supposed file.
 *
 * Return: 122.
 */

int cannotopen(char *file_path)
{
	char *fault, *histoostring;
	int length;

	histoostring = intostr(histo);
	if (!histoostring)
		return (122);

	length = stringlength(name) + stringlength(histoostring)
	 + stringlength(file_path) + 16;
	fault = malloc(sizeof(char) * (length + 1));
	if (!fault)
	{
		free(histoostring);
		return (122);
	}

	stringcopy(fault, name);
	stringconcatenate(fault, ": ");
	stringconcatenate(fault, histoostring);
	stringconcatenate(fault, ": Can't open ");
	stringconcatenate(fault, file_path);
	stringconcatenate(fault, "\n");

	free(histoostring);
	write(STDERR_FILENO, fault, length);
	free(fault);
	return (122);
}

/**
 * filecommands - Takes a file and attempts to run the commands stored.
 * @file_path: Path to the file.
 * @exe_myret: Return value of the last executed command.
 * Return: If file couldn't be opened - 122.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int filecommands(char *file_path, int *exe_myret)
{
	ssize_t file, b_read, i;
	unsigned int range_size = 0;
	unsigned int oldsize = 120;
	char *range, **myargs, **forehead;
	char buffer[120];
	int ret;

	histo = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_myret = cannotopen(file_path);
		return (*exe_myret);
	}
	range = malloc(sizeof(char) * oldsize);
	if (!range)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && range_size == 0)
			return (*exe_myret);
		buffer[b_read] = '\0';
		range_size += b_read;
		range = reallocte(range, oldsize, range_size);
		stringconcatenate(range, buffer);
		oldsize = range_size;
	} while (b_read);
	for (i = 0; range[i] == '\n'; i++)
		range[i] = ' ';
	for (; i < range_size; i++)
	{
		if (range[i] == '\n')
		{
			range[i] = ';';
			for (i += 1; i < range_size && range[i] == '\n'; i++)
				range[i] = ' ';
		}
	}
	myvariable_replacement(&range, exe_myret);
	handle_range(&range, range_size);
	myargs = stringtoken(range, " ");
	free(range);
	if (!myargs)
		return (0);
	if (check_myargs(myargs) != 0)
	{
		*exe_myret = 2;
		free_myargs(myargs, myargs);
		return (*exe_myret);
	}
	forehead = myargs;

	for (i = 0; myargs[i]; i++)
	{
		if (stringncompare(myargs[i], ";", 1) == 0)
		{
			free(myargs[i]);
			myargs[i] = NULL;
			ret = call_myargs(myargs, forehead, exe_myret);
			myargs = &myargs[++i];
			i = 0;
		}
	}

	ret = call_myargs(myargs, forehead, exe_myret);

	free(forehead);
	return (ret);
}

