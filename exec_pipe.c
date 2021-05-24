/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:45:25 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/24 13:02:42 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state		g_state;

void		exec_child_process(t_cmd *cmd, t_cmd *next_cmd, pid_t pid)
{
	int		ret;
	char	*path;
	
	ret = SUCCESS;
	if (pid == 0)
	{
		path = find_extern_dir(next_cmd->token[0]);
		dup2(next_cmd->fd[0], 0);
		close(next_cmd->fd[0]);
		if (check_builtin(next_cmd->token))
			exec_builtin(next_cmd->token);
		else
			(ret = execve(path, next_cmd->token, g_state.env));
		if (ret == -1)
			ft_putstr_fd("command not found\n", STDIN_FILENO);
	}
	else
	{
		path = find_extern_dir(cmd->token[0]);
		dup2(next_cmd->fd[1], 1);
		close(next_cmd->fd[1]);
		if (check_builtin(cmd->token))
			exec_builtin(cmd->token);
		else
			(ret = execve(path, cmd->token, g_state.env));
	}
}

int			exec_pipe(t_cmd **cmd)
{
	pid_t	pid;
	int		status;
	t_cmd	*next_cmd;
	
	next_cmd = *cmd;
	if ((*cmd)->flag == 1)
	{
		next_cmd = (*cmd)->next;
		pipe(next_cmd->fd);
	}
	pid = fork();
	exec_child_process(*cmd, next_cmd, pid);
	waitpid(pid, &status, 0);
	*cmd = (*cmd)->next;
	return (SUCCESS);
}