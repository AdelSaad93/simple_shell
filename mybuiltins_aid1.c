#include "main.h"

void aid_all(void);
void aid_name(void);

/**
 * aid_all - Displays all possible builtin simpleshell commands.
 */
void aid_all(void)
{
	char *letter = "simpleshell\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "Type 'aid' to see this list.\nType 'aid name' to find ";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "out more about the function 'name'.\n\n  name   \t";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "name [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "[DIRECTORY]\n  exit    \texit [STATUS]\n  enviro     \tenviro";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "\n  setenviro  \tsetenviro [VARIABLE] [VALUE]\n  unsetenviro\t";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "unsetenviro [VARIABLE]\n";
	write(STDOUT_FILENO, letter, stringlength(letter));
}


/**
 * aid_name - Displays information on the simpleshell builtin command 'name'.
 */
void aid_name(void)
{
	char *letter = "name: name [NAME[='VALUE'] ...]\n\tHandles namees.\n";

	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "\n\tname: Prints a list of all namees, one per line, in ";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "the format NAME='VALUE'.\n\tname name [name2 ...]:prints";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = " the namees name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "form NAME='VALUE'.\n\tname NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = " an name for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "is already an name, replace its value with VALUE.\n";
	write(STDOUT_FILENO, letter, stringlength(letter));
}

