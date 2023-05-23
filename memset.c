#include "shell.h"
/**
 * set_nulls - sets all the characters in a char array to nulls
 * @arr: Array.
 * @size: array size.
 * Return: void
 */
void set_nulls(char *arr, size_t size)
{
size_t i = 0;
for (; i < size; i++)
arr[i] = '\0';
}
/**
 * set_zeros - sets all the bytes of an integer array to 0
 * @arr: Array.
 * @size: array size.
 * Return: void
 */
void set_zeros(unsigned int *arr, size_t size)
{
size_t i = 0;
for (; i < size; i++)
arr[i] = 0;
}

