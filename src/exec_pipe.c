/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:45:25 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/26 18:08:50 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/fcntl.h>
#include <unistd.h>

int			check_dir_token(char *token)
{
	if (token[0] == '/')
		return (1);
	else if (ft_strncmp(token, "./", 3) == 0)
		return (1);
	else
		return (0);
}

char		*find_extern_dir(char *token)
{
	char		**path_list;
	char		**head;
	char		*dir;
	struct stat	sb;

	if (check_dir_token(token))
		return (token);
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
	if (cmd->flag == 1 || cmd->flag == 0)
		path = find_extern_dir(cmd->token[0]);
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
	if (find_redirection(cmd))
		ft_putstr_fd("bash: redirection error\n", STDERR_FILENO);
	if (check_builtin(cmd->token))
		exec_builtin(cmd);
	else
		ret = execve(path, cmd->token, g_state.env);
	if (ret == -1)
	{
		err_msg_extern(cmd->token[1], strerror(errno));
		exit(errno);
	}
	exit(SUCCESS);
}

int			exec_pipe(t_cmd *cmd)
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
	return (SUCCESS);
}

void		exec_pipe_set(t_cmd **cmd)
{
	t_cmd	*temp;
	int		pipe_cnt;
	int		status;

	temp = *cmd;
	pipe_cnt = 1;
	while (temp)
	{
		if (temp->flag == 0)
			break ;
		pipe_cnt++;
		temp = temp->next;
	}
	while ((*cmd)->flag != 0)
	{
		exec_pipe(*cmd);
		*cmd = (*cmd)->next;
	}
	exec_pipe(*cmd);
	*cmd = (*cmd)->next;
	while (pipe_cnt-- >= 0)
		wait(&status);
	g_state.my_errno = (status >> 8);
}
