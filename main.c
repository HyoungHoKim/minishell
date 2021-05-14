#include "minishell.h"

char		**g_envp = NULL;
int			g_exit_status = 0;

void		process(char *line)
{
	t_cline	*head;

	head = NULL;
	parser(&head, line);
	//cline_print(head);
	tokenizer(&head);
}

// main문에 붙는 3번째 인자는 환경변수를 받는 매개변수이다.
int			main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*line;
	int		ret;

	g_envp = copy_envp(envp);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (1)
	{
		show_prompt();
		if (!get_line(&input))
		{
			free(input);
			ft_putstr_fd("exit\n", STDIN);
			exit(0);
		}
		line = ft_strjoin(input, "\n");
		process(line);
		free(input);
	}
	return (0);
}