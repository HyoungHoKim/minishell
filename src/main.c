/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:44:01 by seushin           #+#    #+#             */
/*   Updated: 2021/05/25 17:46:20 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

t_state		g_state;

int			process(char *line, t_cmd *cmd)
{
	if (cmd->token[0] == NULL)
		return (FAILURE);
	print_cmd_token(cmd);
	while (cmd)
	{
		if (cmd->prev == NULL)
			exec_command(cmd);
		else if (cmd->prev->flag == 0)
			exec_command(cmd);
		else if (cmd->prev->flag == 1 || cmd->flag == 1)
		{
			exec_pipe(cmd);
			//else if (cmd->prev->flag == 2)
			//	exec_redir(cmd);
		}
		cmd = cmd->next;
	}
	if (ft_strlen(line))
		hist_push_front(&g_state.hist, line);
	return (SUCCESS);
}

static int	init(char **line, char **envp)
{
	char		*termtype;
	int			n;

	if (!(g_state.env = copy_envp(envp)))
		return (FAILURE);
	if (!(termtype = getenv("TERM")))
		return (FAILURE);
	if ((n = tgetent(NULL, termtype)) < 1)
		return (FAILURE);
	*line = NULL;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	tcgetattr(STDIN_FILENO, &g_state.backup);
	return (SUCCESS);
}

static void	reset(char **line, t_cmd **cmd)
{
	free(*line);
	*line = NULL;
	free_cmd(*cmd);
	*cmd = NULL;
}

static void	handle_ctrl_d(void)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(g_state.errno);
}

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	if (init(&line, envp))
		return (g_state.errno);
	while (1)
	{
		show_prompt();
		if (get_line(&line) < 1)
			handle_ctrl_d();
		cmd = create_cmd();
		if (parser(line, cmd) == SUCCESS)
			process(line, cmd);
			/*
			** double semi/pipe or unclosed quote
			** TODO: set g_state.errno and write err msg
			*/
		else
			ft_putstr_fd("bash: error\n", STDOUT_FILENO);
		reset(&line, &cmd);
	}
	return (SUCCESS);
}