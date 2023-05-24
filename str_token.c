/**
 * _strtok - separates strings with delimiters
 * @line: Pointer to the input string
 * @delim: Pointer to the delimiter characters
 * Return: A pointer to the created token
 */
char *_strtok(char *line, char *delim)
{
	static char *str = NULL;
	char *copystr;
	int i;

	if (line != NULL)
		str = line;

	if (str == NULL || *str == '\0')
		return NULL;

	copystr = str;

	while (*str)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*str == delim[i])
			{
				*str = '\0';
				str++;
				return copystr;
			}
		}
		str++;
	}

	return copystr;
}
