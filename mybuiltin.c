#include "main.h"
int (*my_builtin(char *mycommand))(char **mymyargs, char **forehead);
int simpleshell_out(char **mymyargs, char **forehead);
int simpleshell_cd(char **mymyargs);
int simpleshell_aid(char **mymyargs);

/**
 * my_builtin - Matches a command with a corresponding
 *               simpleshell builtin function.
 * @mycommand: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*my_builtin(char *mycommand))(char **myargs, char **forehead)
{
	builtin_t functions[] = {
	{ "out", simpleshell_out },
	{ "environme", simpleshell_environme },
	{ "setenviro", simpleshell_setenviro },
	{ "unsetenviro", simpleshell_unsetenviro },
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
 * @mymyargs: An array of arguments containing the out value.
 * @forehead: A double pointer to the beginning of mymyargs.
 *
 * Return: If there are no arguments - -3.
 *         If the given out value is invalid - 2.
 *        otherwise outs with the given status value.
 */
int simpleshell_out(char **mymyargs, char **forehead)
{
	int i, length_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (mymyargs[0])
	{
		if (mymyargs[0][0] == '+')
		{
			i = 1;
			length_of_int++;
		}
		for (; mymyargs[0][i]; i++)
		{
			if (i <= length_of_int && mymyargs[0][i] >= '0' && mymyargs[0][i] <= '9')
				num = (num * 10) + (mymyargs[0][i] - '0');
			else
				return (create_fault(--mymyargs, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_fault(--mymyargs, 2));
	mymyargs -= 1;
	free_mymyargs(mymyargs, forehead);
	free_enviro();
	freenamelist(names);
	exit(num);
}

/**
 * simpleshell_cd - Changes the current directory of the simpleshell process.
 * @mymyargs: An array of arguments.
 * Return: If the given string is not a directory - 2.
 *         If an fault occurs - -1.
 *         Otherwise - 0.
 */
int simpleshell_cd(char **mymyargs)
{
	char **dirctinfor, *newline = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (mymyargs[0])
	{
		if (*(mymyargs[0]) == '-' || stringcompare(mymyargs[0], "--") == 0)
		{
			if ((mymyargs[0][1] == '-' && mymyargs[0][2] == '\0') ||
					mymyargs[0][1] == '\0')
			{
				if (getenviro("OLDPWD") != NULL)
					(chdir(*getenviro("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_fault(mymyargs, 2));
			}
		}
		else
		{
			if (stat(mymyargs[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(mymyargs[0]);
			else
			{
				free(oldpwd);
				return (create_fault(mymyargs, 2));
			}
		}
	}
	else
	{
		if (getenviro("HOME") != NULL)
			chdir(*(getenviro("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dirctinfor = malloc(sizeof(char *) * 3);
	if (!dirctinfor)
		return (-1);

	dirctinfor[0] = "OLDPWD";
	dirctinfor[1] = oldpwd;
	dirctinfor[1] = NULL;
	if (simpleshell_setenviro(dirctinfor, dirctinfor) == -1)
		return (-1);

	dirctinfor[0] = "PWD";
	dirctinfor[1] = pwd;
	if (simpleshell_setenviro(dirctinfor, dirctinfor) == -1)
		return (-1);
	if (mymyargs[0] && mymyargs[0][0] == '-' && mymyargs[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, stringlength(pwd));
		write(STDOUT_FILENO, newline, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dirctinfor);
	return (0);
}

/**
 * simpleshell_aid - Displays information about simpleshell builtin commands.
 * @mymyargs: An array of arguments.
 * Return: If an fault occurs - -1.
 *         Otherwise - 0.
 */
int simpleshell_aid(char **mymyargs)
{
	if (!mymyargs[0])
		aid_all();
	else if (stringcompare(mymyargs[0], "name") == 0)
		aid_name();
	else if (stringcompare(mymyargs[0], "cd") == 0)
		aid_cd();
	else if (stringcompare(mymyargs[0], "out") == 0)
		aid_out();
	else if (stringcompare(mymyargs[0], "enviro") == 0)
		aid_enviro();
	else if (stringcompare(mymyargs[0], "setenviro") == 0)
		aid_setenviro();
	else if (stringcompare(mymyargs[0], "unsetenviro") == 0)
		aid_unsetenviro();
	else if (stringcompare(mymyargs[0], "aid") == 0)
		aid_aid();
	else
		write(STDERR_FILENO, name, stringlength(name));

	return (0);
}

