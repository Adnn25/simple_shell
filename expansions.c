#include "shell.h"

/**

expand_variables - expand variables

@data: a pointer to a struct of the program's data

Return: nothing
*/
void expand_variables(data_of_program *data)
{
int i, j;
char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

if (data->input_line == NULL)
return;

str_copy(line, BUFFER_SIZE, data->input_line);

for (i = 0; line[i]; i++)
{
if (line[i] == '#')
{
line[i--] = '\0';
}
else if (line[i] == '$' && line[i + 1] == '?')
{
line[i] = '\0';
long_to_string(errno, expansion, 10);
str_concat(line, BUFFER_SIZE, expansion);
str_concat(line, BUFFER_SIZE, data->input_line + i + 2);
}
else if (line[i] == '$' && line[i + 1] == '$')
{
line[i] = '\0';
long_to_string((long)getpid(), expansion, 10);
str_concat(line, BUFFER_SIZE, expansion);
str_concat(line, BUFFER_SIZE, data->input_line + i + 2);
}
else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
{
continue;
}
else if (line[i] == '$')
{
for (j = 1; line[i + j] && line[i + j] != ' '; j++)
{
expansion[j - 1] = line[i + j];
}
expansion[j - 1] = '\0';
temp = env_get_key(expansion, data);
line[i] = '\0';
str_concat(line, BUFFER_SIZE, expansion);
if (temp)
{
str_concat(line, BUFFER_SIZE, temp);
}
str_concat(line, BUFFER_SIZE, data->input_line + i + j);
}
}

if (!str_compare(data->input_line, line, 0))
{
free(data->input_line);
data->input_line = str_duplicate(line);
}
}

/**

expand_alias - expand aliases

@data: a pointer to a struct of the program's data

Return: nothing
*/
void expand_alias(data_of_program *data)
{
int i, j, was_expanded = 0;
char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

if (data->input_line == NULL)
return;

str_copy(line, BUFFER_SIZE, data->input_line);

for (i = 0; line[i]; i++)
{
for (j = 0; line[i + j] && line[i + j] != ' '; j++)
{
expansion[j] = line[i + j];
}
expansion[j] = '\0';
 temp = get_alias(data, expansion);
 if (temp)
 {
 	expansion[0] = '\0';
 	str_concat(expansion, BUFFER_SIZE, line + i + j);
 	line[i] = '\0';
 	str_concat(line, BUFFER_SIZE, temp);
 	line[str_length(line)] = '\0';
 	str_concat(line, BUFFER_SIZE, expansion);
 	was_expanded = 1;
 }
 break;
}

if (was_expanded)
{
free(data->input_line);
data->input_line = str_duplicate(line);
}
}

/**

buffer_add - append string at the end of the buffer
@buffer: buffer to be filled
@str_to_add: string to be copied into the buffer
Return: the new length of the buffer
*/
int buffer_add(char *buffer, const char *str_to_add)
{
int length = str_length(buffer);
str_concat(buffer + length, BUFFER_SIZE - length, str_to_add);
return length + str_length(str_to_add);
}
