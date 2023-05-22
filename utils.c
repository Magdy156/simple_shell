#include "shell.h"

/**
 * from_terminal - check the terminal
 * @info: struct address
 * Return: 1 or 0
 */

int from_terminal(info_s *info)
{
	return (isatty(STDIN_FILENO) && info->fd_read <= 2);
}

/**
 * _isalpha - checks if the char is alphabet or not
 * @c: The character to input
 * Return: 1 if c is alphabetic else 0 if not
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - convert a string into an integer
 * @s: the string to be converted
 * Return: integer
 */
int _atoi(char *s)
{
	int sign = 1, i = 0;
	unsigned int res = 0;

	while (!(s[i] <= '9' && s[i] >= '0') && s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] <= '9' && (s[i] >= '0' && s[i] != '\0'))
	{
		res = (res * 10) + (s[i] - '0');
		i++;
	}
	res *= sign;
	return (res);
}

/**
 * is_delimiter - checks if a char is a delimiter or not
 * @c: Char to be checked.
 * @delimiters: string of delimeiters to be compared
 * Return: true if it is a delimiter
 */

bool is_delimiter(char c, char *delimiters)
{
	int i = 0;

	while (delimiters[i])
	{
		if (c == delimiters[i])
			return (true);
		i++;
	}
	return (false);
}
