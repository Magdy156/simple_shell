#include "shell.h"
/**
 * err_num - converts a string to an integer
 * @c: the string to be converted
 * Return: 0 if no numbers in string,
 * converted integer else -1
 */
int err_num(char *c)
{
	int i = 0;
	unsigned long int result = 0;

	if (*c == '+')
		c++;
	while (c[i] != '\0')
	{
		if (c[i] >= '0' && c[i] <= '9')
		{
			result *= 10;
			result += (c[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		i++;
	}
	return (result);
}
/**
 * print_error - prints an error message
 * @info: parameter struct
 * @str: string containing specified error type
 * Return: 0 if no numbers in string,
 * converted integer else -1
 */
void print_error(info_s *info, char *str)
{
	puts_err(info->prog_name);
	puts_err(": ");
	print_dec(info->lines, STDERR_FILENO);
	puts_err(": ");
	puts_err(info->argv[0]);
	puts_err(": ");
	puts_err(str);
}
/**
 * handle_comments - function replaces '#' with '\0'
 * @buff: address of the string to modify
 * Return: 0;
 */

void handle_comments(char *buff)
{
	int i = 0;

	while (buff[i] != '\0')
	{
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
		i++;
	}
}
/**
 * print_dec - function prints a decimal num
 * @input: input
 * @fd: file decriptor
 * Return: number of printed characters
 */
int print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, counter = 0;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = putchar_err;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{

		if (_abs_ / i)
		{
			__putchar('0' + curr / i);
			counter++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	counter++;
	return (counter);
}
/**
 * change_base - changes the base of the num
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *change_base(long int num, int base, int flags)
{
	static char *arr;
	static char buff[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & BAS_CHANGE_UNSIG) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	arr = flags & BAS_CHANGE_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';
	do {
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}
