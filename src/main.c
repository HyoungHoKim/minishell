/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:44:01 by seushin           #+#    #+#             */
/*   Updated: 2021/05/28 14:49:13 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

t_state		g_state;

static int	init(char **line, char **envp)
{
	char		*termtype;
	int			n;

	g_state.my_errno = 1;
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
	g_state.my_errno = 0;
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
	exit(g_state.my_errno);
}

static int	process(t_cmd *cmd)
{
	print_cmd_token(cmd);
	while (cmd)
	{
		if (cmd->token[0] == NULL)
			return (FAILURE);
		if (cmd->flag == PIPE || (cmd->prev && cmd->prev->flag == PIPE))
			exec_pipe_set(&cmd);
		else
			exec_command(&cmd);
	}
	return (SUCCESS);
}

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	if (init(&line, envp))
		return (g_state.my_errno);
	while (1)
	{
		show_prompt();
		if (get_line(&line) < 1)
			handle_ctrl_d();
		cmd = create_cmd();
		if (parser(line, cmd) == SUCCESS)
			process(cmd);
		if (ft_strlen(line))
			hist_push_front(&g_state.hist, line);
		reset(&line, &cmd);
	}
	return (SUCCESS);
}
