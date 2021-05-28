/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:45:25 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/28 15:55:11 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/fcntl.h>
#include <unistd.h>

void		set_pipe(t_cmd *cmd, t_cmd *next_cmd)
{
	if (cmd->flag == PIPE)
	{
		dup2(next_cmd->fd[1], STDOUT_FILENO);
		close(next_cmd->fd[1]);
		close(next_cmd->fd[0]);
	}
	if (cmd->prev && cmd->prev->flag == PIPE)
	{
		dup2(cmd->fd[0], STDIN_FILENO);
		close(cmd->fd[0]);
	}
}

void		exec_child_process(t_cmd *cmd, t_cmd *next_cmd)
{
	int		ret;

	ret = SUCCESS;
	set_pipe(cmd, next_cmd);
	if (find_redirection(cmd) || token_size(cmd->token) == 0)
		exit(g_state.my_errno);
	if (check_builtin(cmd->token))
		exec_builtin(cmd);
	else
		ret = exec_extern(cmd);
	if (ret == -1)
	{
		if (errno == 2)
			err_msg_extern(cmd->token[0], strerror(errno));
		else
			err_msg_extern(cmd->token[1], strerror(errno));
		exit(errno);
	}
	exit(SUCCESS);
}

pid_t		exec_pipe(t_cmd *cmd)
{
	pid_t	pid;
	t_cmd	*next_cmd;

	next_cmd = cmd;
	if (cmd->flag == PIPE)
	{
		next_cmd = cmd->next;
		pipe(next_cmd->fd);
	}
	pid = fork();
	if (pid == 0)
		exec_child_process(cmd, next_cmd);
	if (cmd->flag == PIPE)
		close(next_cmd->fd[1]);
	if (cmd->fd[0] != 0)
		close(cmd->fd[0]);
	return (pid);
}

int			get_pipe_cnt(t_cmd *cmd)
{
	int		pipe_cnt;
	t_cmd	*temp;

	temp = cmd;
	pipe_cnt = 1;
	while (temp)
	{
		if (temp->flag == 0)
			break ;
		pipe_cnt++;
		temp = temp->next;
	}
	return (pipe_cnt);
}

void		exec_pipe_set(t_cmd **cmd)
{
	int		pipe_cnt;
	int		status;
	pid_t	pid;

	pipe_cnt = get_pipe_cnt(*cmd);
	while ((*cmd)->flag != 0)
	{
		exec_pipe(*cmd);
		*cmd = (*cmd)->next;
	}
	if ((*cmd)->token[0] == NULL)
		return (err_msg_multiline(1));
	pid = exec_pipe(*cmd);
	while (pipe_cnt-- > 0)
		if (pid == wait(&status))
			if ((status & 0xff) == 0)
				g_state.my_errno = ((status >> 8) & 0xff);
}
