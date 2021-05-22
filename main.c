/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:44:01 by seushin           #+#    #+#             */
/*   Updated: 2021/05/22 19:33:58 by hari3o           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

t_state		g_state;

void		process(t_cmd *cmd)
{
	print_cmd_token(cmd);
	while (cmd)
	{
		if (cmd->flag == 0)
			exec_command(cmd->token);
		//else if (temp->flag == 1)
		//	exec_pipe(cmd);
		//else if (temp->flag == 2)
		//	exec_redir(cmd);
		cmd = cmd->next;
	}
}

static int	init(char **line, char **envp)
{
	char		*termtype;
	int			n;

	*line = NULL;
	g_state.env = copy_envp(envp);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	tcgetattr(STDIN_FILENO, &g_state.backup);
	if (!(termtype = getenv("TERM")))
		return (FAILURE);
	if ((n = tgetent(NULL, getenv("TERM"))) < 1)
		return (FAILURE);
	return (SUCCESS);
}

static void	reset(char **line, t_cmd **cmd)
{
	free(*line);
	*line = NULL;
	free_cmd(*cmd);
	*cmd = NULL;
}

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	if (init(&line, envp))
		return (FAILURE);
	while (1)
	{
		show_prompt();
		if (get_line(&line) < 1)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			exit(0);
		}
		cmd = create_cmd();
		if (parser(line, cmd))
			ft_putstr_fd("bash: error\n", STDOUT_FILENO);
		else
		{
			process(cmd);
			hist_push_front(&g_state.hist, line);
		}
		reset(&line, &cmd);
	}
	return (SUCCESS);
}
