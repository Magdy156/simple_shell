#include "shell.h"
/**
 * _memset - set a memory of size n with a value b
 * @ptr: the pointer to the target memory
 * @b: the value
 * @n: the amount of bytes to be set
 * Return: a pointer
 */
char *_memset(char *ptr, char b, unsigned int n)
{
unsigned int i = 0;
while (i < n)
{
ptr[i] = b;
i++;
}
return (ptr);
}
/**
 * free_vector - free an allocated memory of strings
 * @vec: pointer to string
 * Return: void.
 */
void free_vector(char **vec)
{
int i = 0;
if (!vec)
return;
for (; *(vec + i); i++)
free(vec[i]);
free(vec);
}
/**
 * _realloc - allocates memory using malloc and free
 * @ptr: pointer to the memory previously allocated with a call to malloc
 * @old_size: the size, in bytes, of the allocated space for ptr
 * @new_size: is the new size, in bytes of the new memory block
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
if (old_size == new_size)
{
return (ptr);
}
if (ptr == NULL)
{
ptr = malloc(new_size);
return (ptr);
}
if (!new_size)
{
free(ptr);
return (NULL);
}
ptr = realloc(ptr, new_size);
return (ptr);
}
/**
 * bfree - NULLs the address after freeing a pointer
 * @ptr: pointer of the pointer to free
 * Return: If successful, 1; otherwise, 0.
 */
int bfree(void **ptr)
{
if (*ptr && ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}

