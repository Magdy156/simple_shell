#include "shell.h"
/**
 * split_string - splits a string into words specified by a delimiter.
* @str: string.
* @separators: One or more delimiters by which to split the string.
* @word_count: Number of words in the string (separated by the delimiters).
* Return: array of pointers to strings.
*/
char **split_string(char *str, char *separators, size_t *word_count)
{
int i, n_words;
char **words;
char *ptr = str;
unsigned int k, w_size[MAX_WORD_COUNT];
set_zeros(w_size, MAX_WORD_COUNT);
n_words = words_count(str, separators, w_size);
if (n_words == 0)
return (NULL);
words = malloc((sizeof(char *) * n_words) +1);
if (!words)
return (NULL);
for (i = 0; i < n_words; i++)
{
words[i] = malloc((sizeof(char) * w_size[i]) + 1);
if (!words[i])
{
for (i--; i >= 0; i--)
free(words[i]);
free(words);
return (NULL);
}
for (k = 0; k < w_size[i]; k++, ptr++)
{
while (is_delimiter(*ptr, separators))
ptr++;
words[i][k] = *ptr;
};
words[i][k] = '\0';
}
*word_count = n_words;
words[i] = NULL;
return (words);
}
/**
 * **strtow - splits a string into words.
 * @str: input string
 * @d: delimeter
 * Return: a pointer to an array of strings
 */
char **strtow(char *str, char *d)
{
int i, j, k, m, n_words = 0;
char **s;
if (!str || str[0] == 0)
return (NULL);
if (!d)
d = " ";
i = 0;
while (str[i] != '\0')
{
if ((!str[i + 1] || is_delimiter(str[i + 1], d)) && !is_delimiter(str[i], d))
n_words++;
i++;
}
if (n_words == 0)
return (NULL);
s = malloc((1 + n_words) *sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < n_words; j++)
{
while (is_delimiter(str[i], d))
i++;
k = 0;
while (str[i + k] && !is_delimiter(str[i + k], d))
k++;
s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (k = 0; k < j; k++)
free(s[k]);
free(s);
return (NULL);
}
for (m = 0; m < k; m++)
s[j][m] = str[i++];
s[j][m] = 0;
}
s[j] = NULL;
return (s);
}

