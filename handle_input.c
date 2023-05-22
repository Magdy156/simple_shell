#include "shell.h"

/**
 * input_buf - reads commands
 * @info: parameter struct
 * @buff: pointer of buffer
 * @len: pointer of length
 * Return: number of read bytes
 */
ssize_t input_buf(info_s *info, char **buff, size_t *len)
{
	ssize_t bytes = 0;
	size_t len_p = 0;

	/* if the buffer is empty, then fill it */
	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		/*Signal Interrupt*/
		signal(SIGINT, handle_sigint);
#if USE_GETLINE
		bytes = getline(buff, &len_p, stdin);
#else
		bytes = _getline(info, buff, &len_p);
#endif
		if (bytes > 0)
		{
			/* remove trailing newline */
			if ((*buff)[bytes - 1] == '\n')
			{
				(*buff)[bytes - 1] = '\0';
				bytes--;
			}
			info->lc_flag = 1;
			handle_comments(*buff);
			update_history(info, *buff, info->hist_lines++);
			{
				*len = bytes;
				info->sep_buff = buff;
			}
		}
	}
	return (bytes);
}

/**
 * get_input - processes the read commands
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t get_input(info_s *info)
{
	static size_t i, j, len;
	static char *buff;
	ssize_t bytes = 0;
	char **buff_p = &(info->arg), *p;

	_putchar(NEG_ONE);
	bytes = input_buf(info, &buff, &len);
	if (bytes == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buff + i;

		check_chain(info, buff, &j, i, len);
		/* iterate to end */
		while (j < len)
		{
			if (is_chain(info, buff, &j))
				break;
			j++;
		}
		i = j + 1;
		/*is it the end of the buff*/
		if (i >= len)
		{
			i = 0;
			len = 0;
			info->sep_buff_kind = REG_FLAG;
		}
		/* move back pointer to current command position */
		*buff_p = p;
		/* return no of bytes in current command */
		return (_strlen(p));
	}
	*buff_p = buff;
	return (bytes);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buff: buffer
 * @size: size
 * Return: bytes number
 */
ssize_t read_buf(info_s *info, char *buff, size_t *size)
{
	ssize_t bytes = 0;

	if (*size)
		return (0);
	bytes = read(info->fd_read, buff, BUFFER_SIZE_READ);
	if (bytes >= 0)
		*size = bytes;
	return (bytes);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer
 * @size: size of preallocated ptr
 * Return: no of read bytes
 */
int _getline(info_s *info, char **ptr, size_t *size)
{
	ssize_t readMe = 0, bytes = 0;
	static char buff[BUFFER_SIZE_READ];
	static size_t i, len;
	size_t j;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && size)
		bytes = *size;
	if (i == len)
		i = len = 0;

	readMe = read_buf(info, buff, &len);
	if (readMe == -1 || (readMe == 0 && len == 0))
		return (-1);
	c = _strchr(buff + i, '\n');
	j = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, bytes, bytes ? bytes + j : j + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (bytes)
		_strncat(new_p, buff + i, j - i);
	else
		_strncpy(new_p, buff + i, j - i + 1);

	bytes += j - i;
	i = j;
	p = new_p;

	if (size)
		*size = bytes;
	*ptr = p;
	return (bytes);
}

/**
 * handle_sigint - prevents ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void handle_sigint(__attribute__((unused)) int sig_num)
{
	_putchar('\n');
	_puts("$ ");
	_putchar(NEG_ONE);
}

