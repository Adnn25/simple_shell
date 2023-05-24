#include "shell.h"

/**
* get_input_line - read one line from the prompt.
* @program_data: struct for the program's data
*
* Return: number of bytes read.
*/
int get_input_line(program_data *data)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	static char *commands_array[10] = {NULL};
	static char operators_array[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	/* check if there are no more commands in the array */
	/* and check the logical operators */
	if (!commands_array[0] || (operators_array[0] == '&' && errno != 0) ||
		(operators_array[0] == '|' && errno == 0))
	{
		/* free the memory allocated in the array if it exists */
		for (i = 0; commands_array[i]; i++)
		{
			free(commands_array[i]);
			commands_array[i] = NULL;
		}

		/* read from the file descriptor into buffer */
		bytes_read = read(data->file_descriptor, &buffer, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* split lines by '\n' or ';' */
		i = 0;
		do {
			commands_array[i] = str_duplicate(_strtok(i ? NULL : buffer, "\n;"));
			/* check and split for '&&' and '||' operators */
			i = check_logical_operators(commands_array, i, operators_array);
		} while (commands_array[i++]);
	}

	/* obtain the next command (command 0) and remove it from the array */
	data->input_line = commands_array[0];
	for (i = 0; commands_array[i]; i++)
	{
		commands_array[i] = commands_array[i + 1];
		operators_array[i] = operators_array[i + 1];
	}

	return (str_length(data->input_line));
}


/**
* check_logical_operators - checks and splits for '&&' and '||' operators
* @commands_array: array of commands.
* @i: index in commands_array to be checked.
* @operators_array: array of logical operators for each previous command.
*
* Return: index of the last command in commands_array.
*/
int check_logical_operators(char *commands_array[], int i, char operators_array[])
{
	char *temp = NULL;
	int j;

	/* checks for the '&' character in the command line */
	for (j = 0; commands_array[i] != NULL  && commands_array[i][j]; j++)
	{
		if (commands_array[i][j] == '&' && commands_array[i][j + 1] == '&')
		{
			/* split the line when '&&' is found */
			temp = commands_array[i];
			commands_array[i][j] = '\0';
			commands_array[i] = str_duplicate(commands_array[i]);
			commands_array[i + 1] = str_duplicate(temp + j + 2);
			i++;
			operators_array[i] = '&';
			free(temp);
			j = 0;
		}
		if (commands_array[i][j] == '|' && commands_array[i][j + 1] == '|')
		{
			/* split the line when '||' is found */
			temp = commands_array[i];
			commands_array[i][j] = '\0';
			commands_array[i] = str_duplicate(commands_array[i]);
			commands_array[i + 1] = str_duplicate(temp + j + 2);
			i++;
			operators_array[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}

