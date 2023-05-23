#include "shell.h"
/**
 * read_hist - reads history file
 * @info: struct
 * Return: string of history file
 */
char *read_hist(info_s *info)
{
char *buf, *dir;
dir = _getenv(info, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE_NAME) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HIST_FILE_NAME);
return (buf);
}
/**
 * create_history - appends to a file if exists
 * @info: struct
 * Return: 1 if succedded, else -1
 */
int create_history(info_s *info)
{
ssize_t f_d;
list_s *node = NULL;
char *filename = read_hist(info);
if (!filename)
return (-1);
f_d = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (f_d == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
write_chars(node->str, f_d);
write_char('\n', f_d);
}
write_char(NEG_ONE, f_d);
close(f_d);
return (1);
}
/**
 * update_history - adds entry to a history linked list
 * @info: simulated arguments
 * @buf: buffer
 * @linecount: history lines
 * Return: 0
 */
int update_history(info_s *info, char *buf, int linecount)
{
list_s *current = NULL;
if (info->history)
current = info->history;
add_node_end(&current, buf, linecount);
if (!info->history)
info->history = current;
return (0);
}
/**
 * read_history - reads history from file
 * @info: the parameter struct
 * Return: hist_lines on success, 0 otherwise
 */
int read_history(info_s *info)
{
ssize_t f_d, rd_len, f_size = 0;
int j, last = 0, linecount = 0;
struct stat st;
char *buf = NULL, *filename = read_hist(info);
if (!filename)
return (0);
f_d = open(filename, O_RDONLY);
free(filename);
if (f_d == -1)
return (0);
if (!fstat(f_d, &st))
f_size = st.st_size;
if (f_size < 2)
return (0);
buf = malloc(sizeof(char) * (f_size + 1));
if (!buf)
return (0);
rd_len = read(f_d, buf, f_size);
buf[f_size] = 0;
if (rd_len <= 0)
return (free(buf), 0);
close(f_d);
for (j = 0; j < f_size; j++)
if (buf[j] == '\n')
{
buf[j] = 0;
update_history(info, buf + last, linecount++);
last = j + 1;
}
if (last != j)
update_history(info, buf + last, linecount++);
free(buf);
info->hist_lines = linecount;
while (info->hist_lines-- >= HIST_SIZE_MAX)
delete_node_at_index(&(info->history), 0);
renumber_history(info);
return (info->hist_lines);
}
/**
 * renumber_history - update the history linked list numbers
 * @info: simulated arguments
 * Return: new history lines
 */
int renumber_history(info_s *info)
{
list_s *current = info->history;
int i = 0;
while (current != NULL)
{
current->num = i++;
current = current->next;
}
return (info->hist_lines = i);
}

