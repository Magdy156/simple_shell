#include "shell.h"

/**
 * _getenv - gets the value of an env var
 * @info: parameter struct
 * @key: env var key
 * Return: the value
 */

char *_getenv(info_s *info, const char *key)
{
	char *ptr;
	list_s *node = info->env;

	while (node)
	{
		ptr = starts_with(node->str, key);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * check_setenv - Checks if an env var has a value.
 * @info: parameter struct
 * Return: 0 if set, otherwise 1.
 */

int check_setenv(info_s *info)
{
	if (info->argc != 3)
	{
		puts_err("number of arguements is not correct\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * check_unsetenv - checks if an env var is removed
 * @info: parameter struct
 * Return: Always 0
 */
int check_unsetenv(info_s *info)
{
	int i = 1;

	if (info->argc == 1)
	{
		puts_err("still need arguements\n");
		return (1);
	}
	while (i <= info->argc)
	{
		_unsetenv(info, info->argv[i]);
		i++;
	}
	return (0);
}

/**
 * gather_env - populates env linked list
 * @info: parameter struct
 * Return: Always 0
 */
int gather_env(info_s *info)
{
	int i = 0;
	list_s *node = NULL;

	while (environ[i])
	{
		add_node_end(&node, environ[i], 0);
		i++;
	}
	info->env = node;
	return (0);
}

/**
 * _printenv - prints the environment
 * @info: parameter struct
 * Return: Always 0
 */
int _printenv(info_s *info)
{
	print_list_str(info->env);
	return (0);
}

