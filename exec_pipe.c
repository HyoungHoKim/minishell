/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:45:25 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/24 21:16:07 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state		g_state;

void		exec_child_process(t_cmd *cmd, t_cmd *next_cmd)
{
	int		ret;
	char	*path;

	ret = SUCCESS;
	path = find_extern_dir(cmd->token[0]);
	if (cmd->flag == 1)
	{
		dup2(next_cmd->fd[1], 1);
		close(next_cmd->fd[1]);
	}
	ft_putstr_fd("test1 \n", STDIN);
	if (cmd->fd[0] != 0)
	{
		dup2(cmd->fd[0], 0);
		close(cmd->fd[0]);
	}
	ft_putstr_fd("test2 \n", STDIN);
	if (check_builtin(cmd->token))
	{
		ft_putstr_fd("builtin exec \n", STDIN);
		exec_builtin(cmd->token);
	}
	else
	{
		ft_putstr_fd("extern_func exec \n", STDIN);
		ret = execve(path, cmd->token, g_state.env);
	}
	if (ret == -1)
		ft_putstr_fd("command not found", STDIN);
	exit(ret);
	
}

int			exec_pipe(t_cmd *cmd)
{
	pid_t	pid;
	t_cmd	*next_cmd;
	int		status;
	
	next_cmd = cmd;
	if (cmd->flag == 1)
	{
		next_cmd = cmd->next;
		pipe(next_cmd->fd);
	}
	pid = fork();
	if (pid == 0)
	{
		ft_putstr_fd("child process start \n", STDIN);
		exec_child_process(cmd, next_cmd);
	}
	waitpid(pid, &status, 0);
	if (cmd->flag == 1)
		close(next_cmd->fd[1]);
	if (cmd->fd[0] != 0)
		close(cmd->fd[0]);
	return (SUCCESS);
}