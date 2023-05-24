#include "shell.h"

int main(int argc, char *argv[], char *envp[])
{
	program_data data_struct = {0};
	program_data *data = &data_struct;
	char *shell_prompt = "";

	initialize_data(data, argc, argv, envp);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		shell_prompt = PROMPT_MSG;
	}

	errno = 0;
	run_shell(shell_prompt, data);

	return 0;
}

void handle_ctrl_c(int unused)
{
	_print("\n");
	_print(PROMPT_MSG);
	(void)unused;
}

void initialize_data(program_data *data, int argc, char *argv[], char *envp[])
{
	int i = 0;

	data->prog_name = argv[0];
	data->input_line = NULL;
	data->cmd_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->fd = STDIN_FILENO;
	else
	{
		data->fd = open(argv[1], O_RDONLY);
		if (data->fd == -1)
		{
			_printe(data->prog_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}

	data->token_values = NULL;

	while (envp[i])
	{
		data->environment[i] = str_duplicate(envp[i]);
		i++;
	}
	data->environment[i] = NULL;

	for (i = 0; i < 20; i++)
		data->alias_list[i] = NULL;
}

void run_shell(char *prompt, program_data *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = read_input_line(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}

		if (string_len >= 1)
		{
			expand_aliases(data);
			expand_variables(data);
			tokenize_input(data);
			
			if (data->token_values[0])
			{
				error_code = execute_command(data);
				if (error_code != 0)
					print_error_message(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}
