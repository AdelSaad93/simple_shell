#include "main.h"

void aid_cd(void);
void aid_exit(void);
void aid_aid(void);

/**
 * aid_cd - Displays information on the simpleshell builtin command 'cd'.
 */
void aid_cd(void)
{
	char *letter = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "\tThe enviroironment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "after a change of directory.\n";
	write(STDOUT_FILENO, letter, stringlength(letter));
}


/**
 * aid_exit - Displays information on the simpleshell builtin command 'exit'.
 */
void aid_exit(void)
{
	char *letter = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = " exit 0.\n";
	write(STDOUT_FILENO, letter, stringlength(letter));
}


/**
 * aid_aid - Displays information on the simpleshell builtin command 'aid'.
 */
void aid_aid(void)
{
	char *letter = "aid: aid\n\tSee all possible simpleshell builtin commands.\n";

	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "\n      aid [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "builtin command.\n";
	write(STDOUT_FILENO, letter, stringlength(letter));
}
