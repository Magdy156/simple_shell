#include "shell.h"

/**
 * is_executable - checks if a file is
 * an executable command or not
 * @info: the info struct
 * @filePath: the file path
 * Return: 1 if true, 0 otherwise
 */
bool is_executable(info_s *info, char *filePath)
{
	struct stat st;

	(void)info;
	if (!filePath || stat(filePath, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (true);
	}
	return (false);
}

/**
 * dup_chars - duplicates chars
 * @pathkey: the PATH key
 * @start: starting index
 * @end: ending index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathkey, int start, int end)
{
	static char buff[1024];
	int i = 0, j = 0;

	for (j = 0, i = start; i < end; i++)
		if (pathkey[i] != ':')
			buff[j++] = pathkey[i];
	buff[j] = 0;
	return (buff);
}

/**
 * check_file_in_path - searches for command in the PATH key
 * @info: the info struct
 * @pathkey: the PATH key
 * @cmd: the command to be found
 * Return: full path of cmd if found or NULL
 */
char *check_file_in_path(info_s *info, char *pathkey, char *cmd)
{
	int i = 0, current = 0;
	char *path;

	if (!pathkey)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_executable(info, cmd))
			return (cmd);
	}
	while (true)
	{
		if (!pathkey[i] || pathkey[i] == ':')
		{
			path = dup_chars(pathkey, current, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_executable(info, path))
				return (path);
			if (!pathkey[i])
				break;
			current = i;
		}
		i++;
	}
	return (NULL);
}

