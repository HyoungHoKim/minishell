#include "minishell.h"
#include <stdlib.h>

t_state		g_state;

void		process(t_cmd *cmd)
{
	char **token = cmd->token;
	int idx = -1;

	cmd = rewind_cmd(cmd);
	while (cmd)
	{
		while (token[++idx] != NULL)
			printf("%s\n", token[idx]);
		cmd = cmd->next;
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
