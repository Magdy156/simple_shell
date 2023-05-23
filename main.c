#include "shell.h"
/**
 * main - Entry point to shell program
 * @argc: arguments count
 * @argv: arguments vectors.
 * Return: 0 if succedded, otherwise 1.
 */
int main(int argc, char **argv)
{
info_s info[] = {SET_INFO};
int f_d = 2;
asm("mov %1, %0\n\t"
"add $3, %0"
: "=r"(f_d)
: "r"(f_d));
if (argc == 2)
{
f_d = open(argv[1], O_RDONLY);
if (f_d == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
puts_err(argv[0]);
puts_err(": 0: Can't open ");
puts_err(argv[1]);
putchar_err('\n');
putchar_err(NEG_ONE);
exit(127);
}
return (EXIT_FAILURE);
}
info->fd_read = f_d;
}
gather_env(info);
read_history(info);
shell_main(info, argv);
return (EXIT_SUCCESS);
}

