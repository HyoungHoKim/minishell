#include "minishell.h"
#include <stdlib.h>

t_state		g_state;

int         check_double_semi(t_cmd *cmd)
{
	int		is_null;
	t_cmd	*temp;

	is_null = 0;
	temp = cmd;
	while (temp)
	{
		if (temp->token[0] == NULL)
		{
			if (is_null)
				return (FAILURE);
			is_null = 1;
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

void		process(t_cmd *cmd)
{
	t_cmd	*temp;

	cmd = rewind_cmd(cmd);
	print_cmd_token(cmd);
	if (check_double_semi(cmd))
		return ;
	temp = cmd;
	while (temp)
	{
		if (temp->flag == 0)
			exec_command(temp->token);
		//else if (temp->flag == 1)
		//	exec_pipe(cmd);
		//else if (temp->flag == 2)
		//	exec_redir(cmd);
		temp = temp->next;
	}
}

// main문에 붙는 3번째 인자는 환경변수를 받는 매개변수이다.
int			main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	*cmd;

	g_state.env = copy_envp(envp);
	cmd = NULL;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (1)
	{
		show_prompt();
		if (!get_line(&input))
		{
			// gnl error.
			free(input);
			ft_putstr_fd("exit\n", STDIN);
			exit(0);
		}
		if (parser(input, &cmd) == EXIT_SUCCESS)
			process(cmd);
		//hist_push_back();
		//free(input);
		free_cmd(cmd);
	}
	return (0);
}
