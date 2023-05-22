#include "shell.h"

/**
 * get_environ - Returns a copy of the environment variables
 * @info: parameter struct
 * Return: array of strings.
 */

char **get_environ(info_s *info)
{
/* If the environment variables dont exist or changed, update them */
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_vector(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _setenv - sets environment variable.
 * @info: parameter struct
 * @key: the key of the env var
 * @value: The value of the environment variable
 * Return: 0 on success, otherwise 1.
 */

int _setenv(info_s *info, char *key, char *value)
{
	char *buff = NULL;
	char *ptr;
	list_s *node;

	if (!key || !value)
		return (1);
	buff = malloc(_strlen(key) + _strlen(value) + 2);
	if (!buff)
		return (1);

	/* Combine the variable name and value into a single string. */
	_strcpy(buff, key);
	_strcat(buff, "=");
	_strcat(buff, value);

	/* Loop through each environment variable. */
	node = info->env;
	while (node)
	{
		/*searches for the key*/
		ptr = starts_with(node->str, key);
		if (ptr && *ptr == '=')
		{
			/*replace*/
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	/* add  env var to the end*/
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}

/**
 * _unsetenv - delets an env var
 * @info: parameter struct
 * @key: the key of the env var
 * Return: 1 on success, otherwise 0.
 */
int _unsetenv(info_s *info, char *key)
{
	char *ptr;
	size_t index = 0;
	list_s *node = info->env;

	if (!node || !key)
		return (0);

	while (node)
	{
		/*searches for the key*/
		ptr = starts_with(node->str, key);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

