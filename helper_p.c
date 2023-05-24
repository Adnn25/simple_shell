#include "shell.h"

/**
 * output_print - writes a char array to the standard output
 * @str: pointer to the array of chars
 * Return: the number of bytes written, or -1 on error.
 */
int output_print(char *str)
{
	return (write(STDOUT_FILENO, str, string_length(str)));
}

/**
 * error_print - writes a char array to the standard error
 * @str: pointer to the array of chars
 * Return: the number of bytes written, or -1 on error.
 */
int error_print(char *str)
{
	return (write(STDERR_FILENO, str, string_length(str)));
}

/**
 * print_error_message - writes an error message to the standard error
 * @err_code: the error code to print
 * @prog_data: pointer to the program's data
 * Return: the number of bytes written, or -1 on error.
 */
int print_error_message(int err_code, program_data *prog_data)
{
	char counter_str[10] = {'\0'};

	convert_long_to_str((long) prog_data->execution_counter, counter_str, 10);

	if (err_code == 2 || err_code == 3)
	{
		error_print(prog_data->prog_name);
		error_print(": ");
		error_print(counter_str);
		error_print(": ");
		error_print(prog_data->token_values[0]);
		if (err_code == 2)
			error_print(": Invalid number: ");
		else
			error_print(": unable to cd to ");
		error_print(prog_data->token_values[1]);
		error_print("\n");
	}
	else if (err_code == 127)
	{
		error_print(prog_data->prog_name);
		error_print(": ");
		error_print(counter_str);
		error_print(": ");
		error_print(prog_data->cmd_name);
		error_print(": not found\n");
	}
	else if (err_code == 126)
	{
		error_print(prog_data->prog_name);
		error_print(": ");
		error_print(counter_str);
		error_print(": ");
		error_print(prog_data->cmd_name);
		error_print(": Permission denied\n");
	}
	return (0);
}
