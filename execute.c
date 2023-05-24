#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**

execute_command - execute a command with its entire path variables.

@data: a pointer to the program's data

Return: If success returns zero, otherwise, return -1.
*/
int execute_command(data_of_program *data)
{
int retval = 0;
pid_t pid;
int status;

/* check for built-in programs */
retval = execute_builtin(data);
if (retval != -1)
return retval;

/* check for program in file system /
retval = find_program(data);
if (retval)
{
/ program not found /
return retval;
}
else
{
:x
 if (pid == -1)
 {
 	/* fork failed */
 	perror("fork");
 	exit(EXIT_FAILURE);
 }

 if (pid == 0)
 {
 	/* I am the child process, I execute the program */
 	retval = execve(data->command_path, data->arguments, data->environment);

 	if (retval == -1)
 	{
 		/* error occurred while executing execve */
 		perror(data->command_name);
 		exit(EXIT_FAILURE);
 	}
 }
 else
 {
 	/* I am the parent, I wait for the child to finish */
 	wait(&status);

 	if (WIFEXITED(status))
 		errno = WEXITSTATUS(status);
 	else if (WIFSIGNALED(status))
 		errno = 128 + WTERMSIG(status);
 }
}

return 0;
}
