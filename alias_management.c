#include "shell.h"

/**
 * print_alias - add, remove or show aliases
 * @program_data: struct for the program's data
 * @alias_name: name of the alias to be printed
 * Return: zero if success, or other number if it's declared in the arguments
 */
int print_alias(program_data *data, char *alias_name)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias_name);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias_name || (str_compare(data->alias_list[i], alias_name, alias_length)
				&&	data->alias_list[i][alias_length] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, remove or show aliases
 * @program_data: struct for the program's data
 * @alias_name: name of the requested alias.
 * Return: zero if success, or other number if it's declared in the arguments
 */
char *get_alias(program_data *data, char *alias_name)
{
	int i, alias_length;

	/* validate the arguments */
	if (alias_name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(alias_name);

	for (i = 0; data->alias_list[i]; i++)
	{
		/* Iterates through the alias list and checks for coincidence of the alias name */
		if (str_compare(alias_name, data->alias_list[i], alias_length) &&
			data->alias_list[i][alias_length] == '=')
		{
			/* returns the value of the alias when found */
			return (data->alias_list[i] + alias_length + 1);
		}
	}
	/* returns NULL if not found */
	return (NULL);
}

/**
 * set_alias - add or override alias
 * @alias_string: alias to be set in the form (name='value')
 * @program_data: struct for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int set_alias(char *alias_string, program_data *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/* validate the arguments */
	if (alias_string == NULL || data->alias_list == NULL)
		return (1);

	/* Iterates through the alias string to find the '=' character */
	for (i = 0; alias_string[i]; i++)
	{
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			/* search if the value of the alias is another alias */
			temp = get_alias(data, alias_string + i + 1);
			break;
		}
	}

	/* Iterates through the alias list and checks for coincidence of the alias name */
	for (j = 0; data->alias_list[j]; j++)
	{
		if (str_compare(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{
			/* if the alias already exists, free the previous entry */
			free(data->alias_list[j]);
			break;
		}
	}

	/* add the alias */
	if (temp)
	{
		/* if the value of the alias is another alias */
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[j] = str_duplicate(buffer);
	}
	else
	{
		/* if the alias does not exist */
		data->alias_list[j] = str_duplicate(alias_string);
	}
	return (0);
}

