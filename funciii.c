#include "shell.h"
/**
 * _strcpy -  copies the string pointed
 * @dest: pointer to a string
 * @src:  pointer to a string
 * Return: pointer to char
 */
char *_strcpy(char *dest, char *src)
{
long int i = 0;
for (; src[i] != '\0'; i++)
{
dest[i] = src[i];
}
dest[i] = '\0';
return (dest);
}
/**
 * _strdup - duplicates a string
 * @str: targeted string
 * Return: pointer to the duplicat
 */
char *_strdup(const char *str)
{
int length = 0;
char *ret;
if (!str)
return (NULL);
while (str[length] != '\0')
length++;
ret = malloc(sizeof(char) * (length + 1));
if (ret == NULL)
return (NULL);
_strcpy(ret, (char *)str);
return (ret);
}
/**
 * _puts - prints every other character of a string
 * @str: the string
 * Return: void
 */
void _puts(char *str)
{
int i = 0;
if (!str)
return;
for (; str[i] != '\0'; i++)
{
_putchar(str[i]);
}
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: 1 if succedded, -1 otherwise.
 */
int _putchar(char c)
{
static int i;
static char buf[BUFFER_SIZE_WRITE];
if (c == NEG_ONE || i >= BUFFER_SIZE_WRITE)
{
write(1, buf, i);
i = 0;
}
if (c != NEG_ONE)
buf[i++] = c;
return (1);
}

