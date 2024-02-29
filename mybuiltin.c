#include "main.h"
int (*my_bultin(char *mycommand))(char **myargs, char **forehead);
int simpleshell_out(char **myargs, char **forehead);
int simpleshell_cd(char **myargs, char  **forehead);
int simpleshell_aid(char **myargs, char  **forehead);

/**
 * my_bultin - Matches a command with a corresponding
 *               simpleshell builtin function.
 * @mycommand: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*my_bultin(char *mycommand))(char **myargs, char **forehead)
{
	builtin_t functions[] = {
		{ "out", simpleshell_out },
		{ "environme", simpleshell_environme },
		{ "setenviro", simpleshell_setenviro },
		{ "unsetenviro", simpleshell_unsetenviro },
		{ "cd", simpleshell_cd },
		{ "name", simpleshell_name },
		{ "aid", simpleshell_aid },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; functions[i].name; i++)
	{
		if (stringcompare(functions[i].name, mycommand) == 0)
			break;
	}
	return (functions[i].f);
}

/**
 * simpleshell_out - Causes normal process termination
 *                for the simpleshell shell.
 * @myargs: An array of arguments containing the out value.
 * @forehead: A double pointer to the beginning of myargs.
 *
 * Return: If there are no arguments - -3.
 *         If the given out value is invalid - 2.
 *        otherwise outs with the given status value.
 *
 */
int simpleshell_out(char **myargs, char **forehead)
{
	int i, length_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (myargs[0])
	{
		if (myargs[0][0] == '+')
		{
			i = 1;
			length_of_int++;
		}
		for (; myargs[0][i]; i++)
		{
			if (i <= length_of_int && myargs[0][i] >= '0' && myargs[0][i] <= '9')
				num = (num * 10) + (myargs[0][i] - '0');
			else
				return (create_fault(--myargs, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_fault(--myargs, 2));
	myargs -= 1;
	free_myargs(myargs, forehead);
	free_enviro();
	free_name_list(names);
	exit(num);
}

/**
 * simpleshell_cd - Changes the current directory of the simpleshell process.
 * @myargs: An array of arguments.
 * @forehead: A double pointer to the beginning of myargs.
 *
 * Return: If the given string is not a directory - 2.
 *         If an fault occurs - -1.
 *         Otherwise - 0.
 */
int simpleshell_cd(char **myargs, char  **forehead)
{
	char **dirctinfor, *newline = "\n";
	char *oldpw = NULL, *pw = NULL;
	struct stat dir;

	oldpw = getcw(oldpw, 0);
	if (!oldpw)
		return (-1);

	if (myargs[0])
	{
		if (*(myargs[0]) == '-' || stringcompare(myargs[0], "--") == 0)
		{
			if ((myargs[0][1] == '-' && myargs[0][2] == '\0') ||
					myargs[0][1] == '\0')
			{
				if (_getenviro("oldpw") != NULL)
					(chdir(*_getenviro("oldpw") + 7));
			}
			else
			{
				free(oldpw);
				return (create_fault(myargs, 2));
			}
		}
		else
		{
			if (stat(myargs[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(myargs[0]);
			else
			{
				free(oldpw);
				return (create_fault(myargs, 2));
			}
		}
	}
	else
	{
		if (_getenviro("HOME") != NULL)
			chdir(*(_getenviro("HOME")) + 5);
	}

	pw = getcw(pw, 0);
	if (!pw)
		return (-1);

	dirctinfor = malloc(sizeof(char *) * 2);
	if (!dirctinfor)
		return (-1);

	dirctinfor[0] = "oldpw";
	dirctinfor[1] = oldpw;
	if (simpleshell_setenviro(dirctinfor, dirctinfor) == -1)
		return (-1);

	dirctinfor[0] = "PWD";
	dirctinfor[1] = pw;
	if (simpleshell_setenviro(dirctinfor, dirctinfor) == -1)
		return (-1);
	if (myargs[0] && myargs[0][0] == '-' && myargs[0][1] != '-')
	{
		write(STDOUT_FILENO, pw, stringlength(pw));
		write(STDOUT_FILENO, newline, 1);
	}
	free(oldpw);
	free(pw);
	free(dirctinfor);
	return (0);
}

/**
 * simpleshell_aid - Displays information about simpleshell builtin commands.
 * @myargs: An array of arguments.
 * @forehead: A pointer to the beginning of myargs.
 *
 * Return: If an fault occurs - -1.
 *         Otherwise - 0.
 */
int simpleshell_aid(char **myargs, char  **forehead)
{
	if (!myargs[0])
		aid_all();
	else if (stringcompare(myargs[0], "name") == 0)
		aid_name();
	else if (stringcompare(myargs[0], "cd") == 0)
		aid_cd();
	else if (stringcompare(myargs[0], "out") == 0)
		aid_out();
	else if (stringcompare(myargs[0], "enviro") == 0)
		aid_enviro();
	else if (stringcompare(myargs[0], "setenviro") == 0)
		aid_setenviro();
	else if (stringcompare(myargs[0], "unsetenviro") == 0)
		aid_unsetenviro();
	else if (stringcompare(myargs[0], "aid") == 0)
		aid_aid();
	else
		write(STDERR_FILENO, name, stringlength(name));

	return (0);
}

