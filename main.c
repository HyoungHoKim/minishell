#include "minishell.h"
#include <stdlib.h>

int			g_exit;

void		process(t_cmd *cmd)
{
}

void		free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
}

// main문에 붙는 3번째 인자는 환경변수를 받는 매개변수이다.
int			main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**env;
	t_cmd	*cmd;

	env = copy_envp(envp);
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
		if (parse(input, cmd) == EXIT_SUCCESS)
			process(cmd);
		free(input);
		free_cmd(cmd);
	}
	return (0);
}
