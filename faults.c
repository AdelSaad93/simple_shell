#include "main.h"

int number_length(int number);
char *intostr(int number);
int create_fault(char **myargs, int fau);

/**
 * number_length - Counts the digit length of a number.
 * @number: The numberber to measure.
 * Return: The digit length.
 */
int number_length(int number)
{
	unsigned int number1;
	int length = 1;

	if (number < 0)
	{
		length++;
		number1 = number * -1;
	}
	else
	{
		number1 = number;
	}
	while (number1 > 9)
	{
		length++;
		number1 /= 10;
	}

	return (length);
}

/**
 * intostr - Converts an integer to a string.
 * @number: The integer.
 *
 * Return: The converted string.
 */
char *intostr(int number)
{
	char *buffer;
	int length = number_length(number);
	unsigned int number1;

	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
		return (NULL);

	buffer[length] = '\0';

	if (number < 0)
	{
		number1 = number * -1;
		buffer[0] = '-';
	}
	else
	{
		number1 = number;
	}

	length--;
	do {
		buffer[length] = (number1 % 10) + '0';
		number1 /= 10;
		length--;
	} while (number1 > 0);

	return (buffer);
}


/**
 * create_fault - Writes a custom fault message to stdfau.
 * @myargs: An array of arguments.
 * @fau: The fault value.
 *
 * Return: The fault value.
 */
int create_fault(char **myargs, int fau)
{
	char *fault;

	switch (fau)
	{
	case -1:
		fault = fault_enviro(myargs);
		break;
	case 1:
		fault = fault_1(myargs);
		break;
	case 2:
		if (*(myargs[0]) == 'e')
			fault = fault_2_exit(++myargs);
		else if (myargs[0][0] == ';' || myargs[0][0] == '&' || myargs[0][0] == '|')
			fault = fault_2_syn(myargs);
		else
			fault = fault_2_cd(myargs);
		break;
	case 404:
		fault = fault_404(myargs);
		break;
	case 505:
		fault = fault_505(myargs);
		break;
	}
	write(STDERR_FILENO, fault, stringlength(fault));

	if (fault)
		free(fault);
	return (fau);

}
