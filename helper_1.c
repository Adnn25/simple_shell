#include "shell.h"

/**
 * release_loop_data - releases the variables used in each loop
 * @app_data: struct containing the program's data
 * Return: None
 */
void release_loop_data(program_data *app_data)
{
	if (app_data->token_values)
		clear_pointer_array(app_data->token_values);
	if (app_data->input_str)
		free(app_data->input_str);
	if (app_data->cmd_name)
		free(app_data->cmd_name);

	app_data->input_str = NULL;
	app_data->cmd_name = NULL;
	app_data->token_values = NULL;
}

/**
 * release_all_data - frees all fields of the program's data
 * @app_data: struct of the program's data
 * Return: None
 */
void release_all_data(program_data *app_data)
{
	if (app_data->fd != 0)
	{
		if (close(app_data->fd))
			perror(app_data->prog_name);
	}
	release_loop_data(app_data);
	clear_pointer_array(app_data->environment);
	clear_pointer_array(app_data->alias_lst);
}

/**
 * clear_pointer_array - frees each pointer in a pointer array and the
 * array itself
 * @ptr_array: array of pointers
 * Return: None
 */
void clear_pointer_array(char **ptr_array)
{
	int index;

	if (ptr_array != NULL)
	{
		for (index = 0; ptr_array[index]; index++)
			free(ptr_array[index]);

		free(ptr_array);
		ptr_array = NULL;
	}
}
