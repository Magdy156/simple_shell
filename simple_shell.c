#include "shell.h"
/**
 * shell_main - main of the shell program
 * @info: pointer to a struct that holds shell information
 * @av: array of strings holds shell arguments
 * Return: last executed builtin command status
 */
int shell_main(info_s *info, char **av)
{
ssize_t r_result = 0;
int value_returned = 0;
while (r_result != -1 && value_returned != -2)
{
clear_info(info);
if (from_terminal(info))
_puts("$ ");
putchar_err(NEG_ONE);
r_result = get_input(info);
if (r_result != -1)
{
set_info(info, av);
value_returned = handle_builtin(info);
if (value_returned == -1)
check_command(info);
}
else if (from_terminal(info))
_putchar('\n');
free_info(info, 0);
}
create_history(info);
free_info(info, 1);
if (!from_terminal(info) && info->status)
exit(info->status);
if (value_returned == -2)
{
if (info->error_code == -1)
exit(info->status);
exit(info->error_code);
}
return (value_returned);
}
/**
 * check_path - Looks for the path
 * @info: a pointer to the info struct
 * Return: void
 */
void check_path(info_s *info)
{
char *path = NULL;
bool check;
path = check_file_in_path(info, _getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
create_process(info);
}
else
{
check = from_terminal(info) || _getenv(info, "PATH=");
check = check || info->argv[0][0] == '/';
if (check && is_executable(info, info->argv[0]))
create_process(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}

/**
 * check_command - Looks for a command both in PATH and in current directory
 * @info: a pointer to the info struct
 * Return: void
 */
void check_command(info_s *info)
{
int j, word_c;
info->path = info->argv[0];
if (info->lc_flag == 1)
{
info->lines++;
info->lc_flag = 0;
}
for (j = 0, word_c = 0; info->arg[j]; j++)
if (!is_delimiter(info->arg[j], " \t\n"))
word_c++;
if (!word_c)
return;
check_path(info);
}

/**
 * handle_builtin - get the builtin command
 * @info: info struct
 * Return: 0 if builtin executed successfully,
 * 1 in case of finding builtin but not successful,
 * 2 if builtin signals exit(),
 * -1 in case of builtin not found
 */
int handle_builtin(info_s *info)
{
int j;
int builtin_return_value = -1;
builtin_commands builtints[] = {
{"cd", handle_cd},
{"env", _printenv},
{"exit", handle_exit},
{"help", handle_help},
{"alias", handle_alias},
{"setenv", check_setenv},
{"history", handle_history},
{"unsetenv", check_unsetenv},
{NULL, NULL}
};
for (j = 0; builtints[j].type; j++)
if (_strcmp(info->argv[0], builtints[j].type) == 0)
{
info->lines++;
builtin_return_value = builtints[j].func(info);
break;
}
return (builtin_return_value);
}

/**
 * create_process - forks a process to execute the command
 * @info: pointer to info struct
 * Return: void
 */
void create_process(info_s *info)
{
pid_t c_pid;
c_pid = fork();
if (c_pid == -1)
{
perror("Error:");
return;
}
if (c_pid == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}

