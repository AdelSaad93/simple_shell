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

	length = stringlengthgth(name) + stringlengthgth(histoostring)
	 + stringlengthgth(file_path) + 16;
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
	unsigned int line_size = 0;
	unsigned int oldsize = 120;
	char *line, **myargs, **front;
	char buffer[120];
	int ret;

	histo = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_myret = cannotopen(file_path);
		return (*exe_myret);
	}
	line = malloc(sizeof(char) * oldsize);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_myret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = realloate(line, oldsize, line_size);
		stringconcatenate(line, buffer);
		oldsize = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_replacement(&line, exe_myret);
	handle_line(&line, line_size);
	myargs = stringtoken(line, " ");
	free(line);
	if (!myargs)
		return (0);
	if (check_myargs(myargs) != 0)
	{
		*exe_myret = 2;
		free_myargs(myargs, myargs);
		return (*exe_myret);
	}
	front = myargs;

	for (i = 0; myargs[i]; i++)
	{
		if (stringncompare(myargs[i], ";", 1) == 0)
		{
			free(myargs[i]);
			myargs[i] = NULL;
			ret = call_myargs(myargs, front, exe_myret);
			myargs = &myargs[++i];
			i = 0;
		}
	}

	ret = call_myargs(myargs, front, exe_myret);

	free(front);
	return (ret);
}
