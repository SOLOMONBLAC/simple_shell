#include "shell.h"

/**
 * is_interactive_mode - checks if the shell is in interactive mode
 * @info: pointer to the shell information struct
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */

int is_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delim: the delimiter string
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_delimiter(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * is_alphabetic - checks if a character is alphabetic
 * @c: the character to check
 *
 * Return: 1 if the character is alphabetic, 0 otherwise
 */
int is_alphabetic(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: the converted integer, 0 if no numbers in the string
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0;
	unsigned int res = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
    {
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			res = res * 10 + (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	return (sign * res);
}
