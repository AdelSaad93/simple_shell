#include "main.h"

void aid_enviro(void);
void aid_setenviro(void);
void aid_unsetenviro(void);
void aid_histo(void);

/**
 * aid_enviro - Displays information on the simpleshell builtin command 'enviro'.
 */
void aid_enviro(void)
{
	char *letter = "enviro: enviro\n\tPrints the current enviroironment.\n";

	write(STDOUT_FILENO, letter, stringlength(letter));
}

/**
 * aid_setenviro - Displays information on the simpleshell builtin command 'setenviro'.
 */
void aid_setenviro(void)
{
	char *letter = "setenviro: setenviro [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "enviroironment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "\tUpon failure, prints a letter to stderr.\n";
	write(STDOUT_FILENO, letter, stringlength(letter));
}

/**
 * aid_unsetenviro - Displays information on the simpleshell builtin command
 * 'unsetenviro'.
 */
void aid_unsetenviro(void)
{
	char *letter = "unsetenviro: unsetenviro [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "enviroironmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, letter, stringlength(letter));
	letter = "letter to stderr.\n";
	write(STDOUT_FILENO, letter, stringlength(letter));
}
