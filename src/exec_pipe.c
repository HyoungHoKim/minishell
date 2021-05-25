/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:45:25 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/25 17:21:25 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state		g_state;

char		*find_extern_dir(char *token)
{
	char		**path_list;
	char		**head;
	char		*dir;
	struct stat	sb;

	path_list = ft_split(get_env_value("PATH"), ':');
	head = path_list;
	token = ft_strjoin("/", token);
	while (*path_list != NULL)
	{
		dir = ft_strjoin(*path_list, token);
		if (stat(dir, &sb) == 0)
			break ;
		free(*path_list);
		free(dir);
		path_list++;
	}
	free(head);
	free(token);
	return (dir);
}

void		exec_child_process(t_cmd *cmd, t_cmd *next_cmd)
{
	int		ret;
	char	*path;

	ret = SUCCESS;
	path = find_extern_dir(cmd->token[0]);
	if (cmd->flag == 1)
	{
		dup2(next_cmd->fd[1], 1);
		close(next_cmd->fd[0]);
	}
	if (cmd->fd[0] != 0)
	{
		dup2(cmd->fd[0], 0);
		close(cmd->fd[0]);
	}
	if (check_builtin(cmd->token))
	{
		exec_builtin(cmd->token);
		close(next_cmd->fd[1]);
	}
	else
		ret = execve(path, cmd->token, g_state.env);
	if (ret == -1)
		ft_putstr_fd("command not found\n", STDOUT_FILENO);
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
		exec_child_process(cmd, next_cmd);
	else
		waitpid(pid, &status, 0);
	if (cmd->flag == 1)
		close(next_cmd->fd[1]);
	if (cmd->fd[0] != 0)
		close(cmd->fd[0]);
	return (SUCCESS);
}