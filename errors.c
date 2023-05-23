#include "shell.h"
/**
 * puts_err - prints a string
 * @str: the string to be printed
 * Return: Nothing
 */
void puts_err(char *str)
{
int j = 0;
if (!str)
return;
for (; str[j] != '\0'; j++)
{
putchar_err(str[j]);
}
}
/**
 * write_char - writes c to given fd
 * @c: character
 * @fd: The filedescriptor to write to
 * Return: 1 if succedded, otherwise -1
 */
int write_char(char c, int fd)
{
static int j;
static char buf[BUFFER_SIZE_WRITE];
if (c == NEG_ONE || j >= BUFFER_SIZE_WRITE)
{
write(fd, buf, j);
j = 0;
}
if (c != NEG_ONE)
buf[j++] = c;
return (1);
}
/**
 * putchar_err - writes c to stderr
 * @c: character
 * Return: 1 if succedded, otherwise -1
 */
int putchar_err(char c)
{
static int j;
static char buf[BUFFER_SIZE_WRITE];
if (c == NEG_ONE || j >= BUFFER_SIZE_WRITE)
{
write(2, buf, j);
j = 0;
}
if (c != NEG_ONE)
buf[j++] = c;
return (1);
}
/**
 * write_chars - prints an input string
 * @str:string
 * @fd: filedescriptor
 * Return: integar
 */
int write_chars(char *str, int fd)
{
int j = 0;
if (!str)
return (0);
while (*str)
{
j += write_char(*str++, fd);
}
return (j);
}

