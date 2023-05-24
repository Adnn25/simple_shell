#include "shell.h"

/**

get_environment_variable - gets the value of an environment variable

@variable: the environment variable of interest

@data: struct of the program's data

Return: a pointer to the value of the variable or NULL if it doesn't exist
*/
char *get_environment_variable(char *variable, data_of_program *data)
{
int i, variable_length = 0;

/* validate the arguments */
if (variable == NULL || data->environment == NULL)
return NULL;

/* obtain the length of the variable requested */
variable_length = str_length(variable);

for (i = 0; data->environment[i]; i++)
{
/* iterate through the environment and check for a match with the variable name /
if (str_compare(variable, data->environment[i], variable_length) &&
data->environment[i][variable_length] == '=')
{
/ returns the value of the variable (NAME=value) when found */
return (data->environment[i] + variable_length + 1);
}
}

/* returns NULL if the variable is not found */
return NULL;
}

/**

set_environment_variable - overwrite the value of the environment variable

or create it if it does not exist.

@variable: name of the variable to set

@value: new value

@data: struct of the program's data

Return: 1 if the parameters are NULL, 2 if there is an error, or 0 if success.
*/
int set_environment_variable(char *variable, char *value, data_of_program *data)
{
int i, variable_length = 0, is_new_variable = 1;

/* validate the arguments */
if (variable == NULL || value == NULL || data->environment == NULL)
return 1;

/* obtain the length of the variable requested */
variable_length = str_length(variable);

for (i = 0; data->environment[i]; i++)
{
/* iterate through the environment and check for a match with the variable name /
if (str_compare(variable, data->environment[i], variable_length) &&
data->environment[i][variable_length] == '=')
{
/ If the variable already exists, free the old value */
is_new_variable = 0;
free(data->environment[i]);
break;
}
}

/* create a string of the form "variable=value" */
data->environment[i] = str_concat(str_duplicate(variable), "=");
data->environment[i] = str_concat(data->environment[i], value);

if (is_new_variable)
{
/* if the variable is new, it is created at the end of the current list and we need /
/ to put the NULL value in the next position */
data->environment[i + 1] = NULL;
}

return 0;
}

/**

remove_environment_variable - remove a variable from the environment

@variable: the variable to remove

@data: the structure of the program's data

Return: 1 if the variable was removed, 0 if the variable does not exist;
*/
int remove_environment_variable(char *variable, data_of_program *data)
{
int i, variable_length = 0;

/* validate the arguments */
if (variable == NULL || data->environment == NULL)
return 0;

/* obtain the length of the variable requested */
variable_length = str_length(variable);

for (i = 0; data->environment[i]; i++)
{
/* iterate through the environment and check for coincidences /
if (str_compare(variable, data->environment[i], variable_length) &&
data->environment[i][variable_length] == '=')
{
/ if the variable already exists, remove it */
free(data->environment[i]);
 	/* move the other variables one position down */
 	i++;
 	for (; data->environment[i]; i++)
 	{
 		data->environment[i - 1] = data->environment[i];
 	}
 	/* put the NULL value at the new end of the list */
 	data->environment[i - 1] = NULL;
 	return 1;
 }
}

return 0;
}

/**

print_environment - prints the current environment

@data: struct for the program's data

Return: nothing
*/
void print_environment(data_of_program *data)
{
int j;

for (j = 0; data->environment[j]; j++)
{
_print(data->environment[j]);
_print("\n");
}
}
