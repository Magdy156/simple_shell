#include "shell.h"

/**
 * add_node_start -  adds a new node at the beginnin
 * @head: address of pointer to the head
 * @str: data to be inserted
 * @index: node index used by history
 * Return:  pointer to the new node, or NULL if it fails
 */
list_s *add_node_start(list_s **head, const char *str, int index)
{
	list_s *new;

	if (!head)
		return (NULL);
	new = malloc(sizeof(list_s));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_s));
	new->num = index;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *head;
	*head = new;
	return (new);
}

/**
 * add_node_end - adds a new node at the end
 * @head: address of pointer to head node
 * @str: data to be inserted
 * @index: node index used by history
 *
 * Return: size of list
 */
list_s *add_node_end(list_s **head, const char *str, int index)
{
	list_s *new, *node;

	if (!head)
		return (NULL);

	node = *head;
	new = malloc(sizeof(list_s));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_s));
	new->num = index;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*head = new;
	return (new);
}

/**
 * print_list_str - prints only the str element of a list_s linked list
 * @first: pointer to first node
 * Return: size of list
 */
size_t print_list_str(const list_s *first)
{
	size_t size = 0;

	while (first)
	{
		_puts(first->str ? first->str : "(nil)");
		_putchar('\n');
		first = first->next;
		size++;
	}
	return (size);
}

/**
 * delete_node_at_index -  deletes a node by index
 * @head: address of pointer to first node
 * @index: index of node to be deleted
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_s **head, unsigned int index)
{
	list_s *prev_node, *node;
	unsigned int i;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	for (i = 0; node; i++)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 * Return: void
 */
void free_list(list_s **head_ptr)
{
	list_s *node, *next, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next = node->next;
		free(node->str);
		free(node);
		node = next;
	}
	*head_ptr = NULL;
}

