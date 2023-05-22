#include "shell.h"
/**
 * unset_alias - unsets alias to string
 * @info: parameter struct
 * @str: the  alias
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_s *info, char *str)
{
	char *ptr, c;
	int result;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	result = delete_node_at_index(&(info->alias),
								  get_node_index(info->alias, node_str_start(info->alias, str, -1)));
	*ptr = c;
	return (result);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the alias
 * Return: 0 on success, 1 on error
 */
int set_alias(info_s *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias
 * @node: the alias node
 * Return: 0 on success, 1 on error
 */
int print_alias(list_s *node)
{
	char *ptr = NULL, *c = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		c = node->str;
		while (c <= ptr)
		{
			_putchar(*c);
			c++;
		}
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * change_alias - replaces an alias in tokenized string
 * @info: the parameter struct
 * Return: 1 on success, 0 otherwise
 */
int change_alias(info_s *info)
{
	unsigned int i = 0;
	char *ptr;
	list_s *node;

	while (i < 10)
	{
		node = node_str_start(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
		i++;
	}
	return (1);
}

/**
 * handle_alias - mimics the alias builtin (man alias)
 * @info: parameter struct
 * Return: Always 0
 */
int handle_alias(info_s *info)
{
	int i = 1;
	char *c = NULL;
	list_s *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	while (info->argv[i])
	{
		c = _strchr(info->argv[i], '=');
		if (c)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_str_start(info->alias, info->argv[i], '='));
		i++;
	}
	return (0);
}
