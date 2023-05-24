#include "shell.h"

int check_file(const char *full_path);

/**

find_program - find a program in the PATH environment variable

@data: a pointer to the program's data

Return: 0 if success, errcode otherwise
*/
int find_program(data_of_program *data)
{
int i = 0, ret_code = 0;
char **directories;

if (!data->command_name)
return (2);

/* If it is a full path or an executable in the same path */
if (data->command_name[0] == '/' || data->command_name[0] == '.')
return (check_file(data->command_name));

free(data->tokens[0]);
data->tokens[0] = str_concat("/", data->command_name);
if (!data->tokens[0])
return (2);

directories = tokenize_path(data); /* Search in the PATH */

if (!directories || !directories[0])
{
errno = 127;
return (127);
}

for (i = 0; directories[i]; i++)
{
/* Append the command_name to the path */
char *full_path = str_concat(directories[i], data->tokens[0]);
if (!full_path)
{
free_array_of_pointers(directories);
return (2);
}
 ret_code = check_file(full_path);
 if (ret_code == 0 || ret_code == 126)
 {
 	/* The file was found, is not a directory, and has execute permissions */
 	errno = 0;
 	free(data->tokens[0]);
 	data->tokens[0] = str_duplicate(full_path);
 	free(full_path);
 	free_array_of_pointers(directories);
 	return (ret_code);
 }

 free(full_path);
}

free(data->tokens[0]);
data->tokens[0] = NULL;
free_array_of_pointers(directories);
return (ret_code);
}

/**

tokenize_path - tokenize the PATH environment variable into directories

@data: a pointer to the program's data

Return: array of path directories
*/
char **tokenize_path(data_of_program *data)
{
int i, counter_directories = 0;
char **tokens = NULL;
char *PATH = env_get_key("PATH", data);

if (!PATH || PATH[0] == '\0')
return (NULL);

for (i = 0; PATH[i]; i++)
{
if (PATH[i] == ':')
counter_directories++;
}

tokens = malloc(sizeof(char *) * (counter_directories + 2));
if (!tokens)
return (NULL);

i = 0;
tokens[i] = str_duplicate(_strtok(PATH, ":"));
while (tokens[i++])
tokens[i] = str_duplicate(_strtok(NULL, ":"));

return (tokens);
}

/**

check_file - checks if a file exists, if it is not a directory, and

if it has execute permissions.

@full_path: pointer to the full file path

Return: 0 on success, or error code if it doesn't exist or is not executable.
*/
int check_file(const char *full_path)
{
struct stat sb;

if (stat(full_path, &sb) != -1)
{
if (S_ISDIR(sb.st_mode) || access(full_path, X_OK) != 0)
{
errno = 126;
return (126);
}
return (0);
}

/* File does not exist */
errno = 127;
return (127);
}
