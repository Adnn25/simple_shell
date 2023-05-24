/**
 * tokenize - separates the string using a designated delimiter
 * @data: Pointer to the program's data
 * Return: An array of the different parts of the string
 */
void tokenize(data_of_program *data)
{
	char *delimiter = " \t";
	int i, counter = 2, length;

	length = str_length(data->input_line);
	if (length > 0)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (i = 0; data->input_line[i]; i++)
	{
		if (strchr(delimiter, data->input_line[i]) != NULL)
			counter++;
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}

	i = 0;
	data->tokens[i] = str_duplicate(_strtok(data->input_line, delimiter));
	data->command_name = str_duplicate(data->tokens[0]);
	i = 1;
	while ((data->tokens[i] = str_duplicate(_strtok(NULL, delimiter))) != NULL)
		i++;
}
