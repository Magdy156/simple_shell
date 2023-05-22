#include "shell.h"
/**
 * clear_info - clears info_s struct
 * @info: parameter struct
 */
void clear_info(info_s *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * set_info - initializes info_s struct
 * @info: parameter struct
 * @argv: argument vector
 */
void set_info(info_s *info, char **argv)
{
	int i = 0;

	info->prog_name = argv[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		while (info->argv && info->argv[i])
			i++;
		info->argc = i;
		change_v(info);
		change_alias(info);
	}
}
/**
 * free_info - frees info_s struct
 * @info: parameter struct
 * @all: 1 for freeing all properties of the struct
 * 0 for only path and argv
 */
void free_info(info_s *info, int all)
{
	free_vector(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (!info->sep_buff)
			free(info->arg);
		if (info->alias)
			free_list(&(info->alias));
		free_vector(info->environ);
		info->environ = NULL;
		bfree((void **)info->sep_buff);
		if (info->fd_read > 2)
			close(info->fd_read);
		_putchar(NEG_ONE);
	}
}

