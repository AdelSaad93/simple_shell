#include "main.h"

int tokenlengthgth(char *str, char *delimiter);
int count_tokens(char *str, char *delimiter);
char **stringtoken(char *range, char *delimiter);

/**
 * tokenlengthgth - Locates the delimiter index marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @delimiter: The delimiter character.
 *
 * Return: The delimiter index marking the end of
 *         the intitial token pointed to be str.
 */
int tokenlengthgth(char *str, char *delimiter)
{
	int index = 0, length = 0;

	while (*(str + index) && *(str + index) != *delimiter)
	{
		length++;
		index++;
	}

	return (length);
}

/**
 * count_tokens - Counts the number of delimiterited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delimiter: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int count_tokens(char *str, char *delimiter)
{
	int index, tokens = 0, length = 0;

	for (index = 0; *(str + index); index++)
		length++;

	for (index = 0; index < length; index++)
	{
		if (*(str + index) != *delimiter)
		{
			tokens++;
			index += tokenlengthgth(str + index, delimiter);
		}
	}

	return (tokens);
}

/**
 * stringtoken - Tokenizes a string.
 * @range: The string.
 * @delimiter: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **stringtoken(char *range, char *delimiter)
{
	char **pointer;
	int index = 0, tokens, t, letters, l;

	tokens = count_tokens(range, delimiter);
	if (tokens == 0)
		return (NULL);

	pointer = malloc(sizeof(char *) * (tokens + 2));
	if (!pointer)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (range[index] == *delimiter)
			index++;

		letters = tokenlengthgth(range + index, delimiter);

		pointer[t] = malloc(sizeof(char) * (letters + 1));
		if (!pointer[t])
		{
			for (index -= 1; index >= 0; index--)
				free(pointer[index]);
			free(pointer);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			pointer[t][l] = range[index];
			index++;
		}

		pointer[t][l] = '\0';
	}
	pointer[t] = NULL;
	pointer[t + 1] = NULL;

	return (pointer);
}
