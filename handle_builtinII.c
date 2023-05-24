#include "shell.h"

/**
 * handle_exit - exits the the program
 * @info: parameter struct
 * Return: exits with status
 * (0) if info.argv[0] != "exit"
 */

int handle_exit(info_s *info)
{
	int exit_check;

	/* if exit arguement exists */
	if (info->argv[1])
	{
		exit_check = err_num(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			puts_err(info->argv[1]);
			putchar_err('\n');
			return (1);
		}
		info->error_code = err_num(info->argv[1]);
		return (-2);
	}
	info->error_code = -1;
	return (-2);
}
/**
 * handle_cd - changes the current directory
 * @info: parameter struct
 * Return: 0 Always
 */

int handle_cd(info_s *info)
{
	char *str, *dir, buff[1024];
	int chdir_ret;

	str = getcwd(buff, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't change dir to ");
		puts_err(info->argv[1]), putchar_err('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * handle_help - prints a message for not implemented func
 * @info: parameter struct
 * Return: 0 Always
 */

int handle_help(__attribute__((unused)) info_s *info)
{
	_puts("Function has not been implemented yet\n");
	return (0);
}

/**
 * handle_history - displays the history list
 * @info: parameter struct
 * Return: Always 0
 */

int handle_history(info_s *info)
{
	print_list(info->history);
	return (0);
}

