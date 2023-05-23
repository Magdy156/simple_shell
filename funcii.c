#include "shell.h"

/**
 * _strncpy - copy n of characters from one string to another
 * @dest: pointer to a string
 * @src: pointer to the second string
 * @n: n bytes from src
 * Return: pointer to char
 */
char *_strncpy(char *dest, char *src, int n)
{
int i, j;
char *s = dest;
i = 0;
for (; i < n - 1; i++)
{
if (src[i] == '\0')
break;
dest[i] = src[i];
}
if (i < n)
{
j = i;
for (; j < n; j++)
{
dest[j] = '\0';
}
}
return (s);
}
/**
**_strncat - concatenates two strings
*@dest: the first string
*@src: the second string
*@n: the amount of bytes to be maximally used
*Return: the concatenated string
*/
char *_strncat(char *dest, char *src, int n)
{
int i, j;
char *s = dest;
i = 0;
j = 0;
while (dest[i] != '\0')
i++;
for (; j < n; j++)
{
if (src[j] == '\0')
break;
dest[i] = src[j];
i++;
}
if (j < n)
dest[i] = '\0';
return (s);
}
/**
 * _strchr - locates a character in a string
 * @s: pointer to a string
 * @c: charachter
 * Return: pointer to the charachter
 */
char *_strchr(char *s, char c)
{
while (*s != '\0')
{
if (*s == c)
return (s);
s++;
}
return (NULL);
}

