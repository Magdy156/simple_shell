#include "shell.h"
/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buff: buffer
 * @current: pointer to current position in buff
 *
 * Return: 1 if chain delimeter else 0
 */
bool is_chain(info_s *info, char *buff, size_t *current)
{
	size_t i = *current;

	if (buff[i] == '&' && buff[i + 1] == '&')
	{
		buff[i] = 0;
		i++;
		info->sep_buff_kind = AND_FLAG;
	}
	else if (buff[i] == '|' && buff[i + 1] == '|')
	{
		buff[i] = 0;
		i++;
		info->sep_buff_kind = OR_FLAG;
	}
	else if (buff[i] == ';')
	{
		buff[i] = 0;
		info->sep_buff_kind = CHAIN_FLAG;
	}
	else
		return (false);
	*current = i;
	return (true);
}

/**
 * check_chain - checks if we should continue chaining
 * according to the last status
 * @info: the parameter struct
 * @buff: the buffer
 * @curr: pointer to current position in buff
 * @i: starting position in buff(counter)
 * @len: buffer length
 * Return: Void
 */
void check_chain(info_s *info, char *buff, size_t *curr, size_t i, size_t len)
{
	size_t j = *curr;

	if (info->sep_buff_kind == AND_FLAG)
	{
		if (info->status)
		{
			buff[i] = 0;
			j = len;
		}
	}
	if (info->sep_buff_kind == OR_FLAG)
	{
		if (!info->status)
		{
			buff[i] = 0;
			j = len;
		}
	}
	*curr = j;
}

/**
 * change_v - replaces vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 on success, 0 otherwise
 */
int change_v(info_s *info)
{
	int j = 0;
	list_s *node;

	for (j = 0; info->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;
		if (!_strcmp(info->argv[j], "$?"))
		{
			change_string(&(info->argv[j]),
						  _strdup(change_base(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[j], "$$"))
		{
			change_string(&(info->argv[j]),
						  _strdup(change_base(getpid(), 10, 0)));
			continue;
		}
		node = node_str_start(info->env, &info->argv[j][1], '=');
		if (node)
		{
			change_string(&(info->argv[j]),
						  _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		change_string(&info->argv[j], _strdup(""));
	}
	return (0);
}
/**
 * change_string - replaces string by another
 * @old_str: pointer to of old string
 * @new_str: new string
 * Return: 1 if replaced
 */
int change_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;

	return (1);
}

