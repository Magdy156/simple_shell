#include "shell.h"
/**
 * _strlen - returns the length of a string
 * @s: pointer to a string
 * Return: the length of a string
 */
int _strlen(char *s)
{
int i = 0;
if (!s)
return (0);
while (s[i] != '\0')
i++;
return (i);
}
/**
 * _strcmp - determine the relative order of two strings.
 * @s1: first string
 * @s2: second string
 * Return: - if s1 < s2, + if s1 > s2, and 0 if s1 equals s2
 */
int _strcmp(char *s1, char *s2)
{
int i = 0;
while (s1[i] && s2[i])
{
if (s1[i] != s2[i])
return (s1[i] - s2[i]);
i++;
}
if (s1[i] == s2[i])
return (0);
else
return (s1[i] < s2[i] ? -1 : 1);
}
/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}
/**
 * _strcat - concatenates two strings
 * @dest: destination
 * @src: the source
 * Return: pointer to the destination
 */
char *_strcat(char *dest, char *src)
{
char *ret = dest;
int i = 0;
int j = 0;
while (dest[i] != '\0')
i++;
while (src[j])
{
dest[i] = src[j];
j++;
i++;
}
dest[i] = src[j];
return (ret);
}

