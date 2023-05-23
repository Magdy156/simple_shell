#include "shell.h"
/**
 * _listlen - gets the length of linked list
 * @h: list head.
 * Return:  the number of nodes.
 */
size_t _listlen(const list_s *h)
{
size_t num = 0;
const list_s *current = h;
while (current != NULL)
{
num += 1;
current = current->next;
}
return (num);
}
/**
 * list_to_vector - returns an array of strings of the list->str
 * @head: pointer to first node
 * Return: Array of strings.
 */
char **list_to_vector(list_s *head)
{
list_s *current = head;
size_t len = _listlen(head), j;
char **strs;
char *str;
if (!head || !len)
return (NULL);
strs = malloc(sizeof(char *) * (len + 1));
if (!strs)
return (NULL);
for (len = 0; current; current = current->next, len++)
{
str = malloc(_strlen(current->str) + 1);
if (!str)
{
for (j = 0; j < len; j++)
free(strs[j]);
free(strs);
return (NULL);
}
str = _strcpy(str, current->str);
strs[len] = str;
}
strs[len] = NULL;
return (strs);
}
/**
 * node_str_start - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to check
 * @c: the next character after prefix to check
 * Return: match node or null
 */
list_s *node_str_start(list_s *node, char *prefix, char c)
{
char *p = NULL;
while (node)
{
p = starts_with(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}
/**
 * print_list - prints all elements of a list_s linked list
 * @h: pointer to first node
 * Return: Size of list
 */
size_t print_list(const list_s *h)
{
size_t num = 0;
const list_s *current = h;
while (current != NULL)
{
_puts(change_base(current->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(current->str ? current->str : "(nil)");
_puts("\n");
current = current->next;
num++;
}
return (num);
}
/**
 * get_node_index - gets the index of a certain node
 * @head: pointer to the head
 * @node: pointer to target node
 * Return: node index.
 */
ssize_t get_node_index(list_s *head, list_s *node)
{
size_t i = 0;
list_s *current = head;
while (current)
{
if (current == node)
return (i);
current = current->next;
i++;
}
return (-1);
}

