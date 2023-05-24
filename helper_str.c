#include "shell.h"

/**
 * get_string_length - returns the length of a string.
 * @str: pointer to string.
 * Return: length of string.
 */
int get_string_length(char *str)
{
	int length = 0;

	if (str == NULL)
		return 0;

	while (str[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * duplicate_string - duplicates a string
 * @str: String to be copied
 * Return: pointer to the duplicated array
 */
char *duplicate_string(char *str)
{
	char *result;
	int length, i;

	if (str == NULL)
		return NULL;

	length = get_string_length(str) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return NULL;
	}

	for (i = 0; i < length; i++)
	{
		result[i] = str[i];
	}

	return result;
}

/**
 * compare_strings - Compare two strings
 * @str1: String one, or the shorter
 * @str2: String two, or the longer
 * @num_chars: number of characters to be compared, 0 if infinite
 * Return: 1 if the strings are equal, 0 if the strings are different
 */
int compare_strings(char *str1, char *str2, int num_chars)
{
	int i;

	if (str1 == NULL && str2 == NULL)
		return 1;

	if (str1 == NULL || str2 == NULL)
		return 0;

	if (num_chars == 0) /* infinite length */
	{
		if (get_string_length(str1) != get_string_length(str2))
			return 0;

		for (i = 0; str1[i]; i++)
		{
			if (str1[i] != str2[i])
				return 0;
		}
		return 1;
	}
	else /* if there is a specific number of chars to be compared */
	{
		for (i = 0; i < num_chars; i++)
		{
			if (str1[i] != str2[i])
				return 0;
		}
		return 1;
	}
}

/**
 * concatenate_strings - concatenates two strings.
 * @str1: String to be concatenated
 * @str2: String to be concatenated
 * Return: pointer to the concatenated string
 */
char *concatenate_strings(char *str1, char *str2)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (str1 == NULL)
		str1 = "";
	length1 = get_string_length(str1);

	if (str2 == NULL)
		str2 = "";
	length2 = get_string_length(str2);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return NULL;
	}

	/* copy str1 */
	for (length1 = 0; str1[length1] != '\0'; length1++)
		result[length1] = str1[length1];
	free(str1);

	/* copy str2 */
	for (length2 = 0; str2[length2] != '\0'; length2++)
	{
		result[length1] = str2[length2];
		length1++;
	}

	result[length1] = '\0';
	return result;
}

/**
 * reverse_string - reverses a string.
 *
 * @str: pointer to string.
 * Return: void.
 */
void reverse_string(char *str)
{
	int i = 0, length = get_string_length(str) - 1;
	char temp;

	while (i < length)
	{
		temp = str[i];
		str[i++] = str[length];
		str[length--] = temp;
	}
}
