#include "shell.h"

void point_to_char(char *strCpy, char *separators);
/**
 * words_count - counts the number of words in a string separated by
 * one or more delimiter. It also counts the length of
 * each word and stores them in an array.
 * @str: string to be iterated.
 * @separators: delimiters
 * @arr: Pointer to the array
 * Return: words number.
 */

int words_count(char *str, char *separators, unsigned int *arr)
{
	unsigned int j, word_length = 1;
	unsigned int word_counter = 0;
	char *strCpy = str;
	bool delimiter;

	if (!str)
		return (0);

	/*point to first non-delimiter character */
	point_to_char(strCpy, separators);

	/* If the word consists of one char*/
	if (!*(strCpy + 1))
	{
		arr[0] = 1;
		return (1);
	}

	for (j = 1; strCpy[j]; j++)
	{
		/* Compare delimiters with the current char */
		delimiter = is_delimiter(strCpy[j], separators);

		/* If current char is a delimiter and previous char is not */
		if (delimiter && !(is_delimiter(strCpy[j - 1], separators)))
		{
			arr[word_counter] = word_length;
			word_counter++;
		}
		/* If we're at the end of the string and its not a delimiter */
		if ((!strCpy[j + 1]) && !delimiter)
		{
			word_length++;
			arr[word_counter] = word_length;
			word_counter++;
			break;
		}
		if (!delimiter)
			word_length++;
		else
			word_length = 0;
	}
	return (word_counter);
}

/**
 * point_to_char - points to first non-delimiter character
 * @strCpy: string
 * @separators: string
 * Return: void
 */
void point_to_char(char *strCpy, char *separators)
{
	unsigned int i = 0;
	bool start = false;

	while (!start)
		while (separators[i])
		{
			if (*strCpy == separators[i])
				strCpy++;
			else
				start = true;
			i++;
		}
}
