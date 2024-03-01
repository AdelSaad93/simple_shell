#include "main.h"

char *fillpathdirctorector(char *path);
list_t *getpathdirctorector(char *path);

/**
 * getlocation - Locates a command in the PATH.
 * @command: The command to locate.
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *getlocation(char *command)
{
	char **path, *temp;
	list_t *dirctors, *head;
	struct stat st;

	path = getenviro("PATH");
	if (!path || !(*path))
		return (NULL);

	dirctors = getpathdirctorector(*path + 5);
	head = dirctors;

	while (dirctors)
	{
		temp = malloc(stringlength(dirctors->dirctor) + stringlength(command) + 2);
		if (!temp)
			return (NULL);

		stringcopy(temp, dirctors->dirctor);
		stringconcatenate(temp, "/");
		stringconcatenate(temp, command);

		if (stat(temp, &st) == 0)
		{
			freelist(head);
			return (temp);
		}

		dirctors = dirctors->next;
		free(temp);
	}

	freelist(head);

	return (NULL);
}

/**
 * fillpathdirctorector - Copies path but also replaces.
 * @path: The colon-separated list of dirctorectories.
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working dirctorectory.
 */
char *fillpathdirctorector(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(getenviro("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += stringlength(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				stringconcatenate(path_copy, pwd);
				stringconcatenate(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				stringconcatenate(path_copy, ":");
				stringconcatenate(path_copy, pwd);
			}
			else
				stringconcatenate(path_copy, ":");
		}
		else
		{
			stringnconcatenate(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * getpathdirctorector - Tokenizes a colon-separated list of
 *                dirctorectories into a list_s linked list.
 * @path: The colon-separated list of dirctorectories.
 * Return: A pointer to the initialized linked list.
 */
list_t *getpathdirctorector(char *path)
{
	int index;
	char **dirctors, *path_copy;
	list_t *head = NULL;

	path_copy = fillpathdirctorector(path);
	if (!path_copy)
		return (NULL);
	dirctors = stringtoken(path_copy, ":");
	free(path_copy);
	if (!dirctors)
		return (NULL);

	for (index = 0; dirctors[index]; index++)
	{
		if (addnodeend(&head, dirctors[index]) == NULL)
		{
			freelist(head);
			free(dirctors);
			return (NULL);
		}
	}

	free(dirctors);

	return (head);
}

