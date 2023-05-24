#include "shell.h"

/**
 * convert_long_to_str - transforms a numerical value to a string.
 * @num: number to be transformed into a string.
 * @str: buffer to store the converted number.
 * @base: base for number conversion
 *
 * Return: Nothing.
 */
void convert_long_to_str(long num, char *str, int base)
{
	int i = 0, isNegative = 0;
	long quotient = num;
	char digits[] = {"0123456789abcdef"};

	if (quotient == 0)
		str[i++] = '0';

	if (str[0] == '-')
		isNegative = 1;

	while (quotient)
	{
		if (quotient < 0)
			str[i++] = digits[-(quotient % base)];
		else
			str[i++] = digits[quotient % base];
		quotient /= base;
	}
	if (isNegative)
		str[i++] = '-';

	str[i] = '\0';
	str_reverse(str);
}


/**
 * convert_str_to_int - transform a string to an integer.
 *
 * @src_str: source string.
 * Return: integer conversion of string or 0.
 */
int convert_str_to_int(char *src_str)
{
	int sign_val = 1;
	unsigned int num = 0;

	/*1- analyse sign*/
	while (!('0' <= *src_str && *src_str <= '9') && *src_str != '\0')
	{
		if (*src_str == '-')
			sign_val *= -1;
		if (*src_str == '+')
			sign_val *= +1;
		src_str++;
	}

	/*2 - extract the number */
	while ('0' <= *src_str && *src_str <= '9' && *src_str != '\0')
	{
		num = (num * 10) + (*src_str - '0');
		src_str++;
	}
	return (num * sign_val);
}

/**
 * count_char_occurrences - count the instances of a character in a string.
 *
 * @str: source string.
 * @char_to_count: char to count in the string
 * Return: int count of occurrences or 0.
 */
int count_char_occurrences(char *str, char *char_to_count)
{
	int i = 0, count = 0;

	for (; str[i]; i++)
	{
		if (str[i] == char_to_count[0])
			count++;
	}
	return (count);
}
