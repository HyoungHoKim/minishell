/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:44:14 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/24 14:53:36 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int			extern_func(char **token)
{
	char		*dir;
	pid_t		pid;
	int			ret;
	int			status;

	dir = find_extern_dir(token[0]);
	pid = fork();
	if (pid == 0)
	{
		if ((ret = execve(dir, token, g_state.env)) == -1)
		{
			ft_putstr_fd("command not found\n", STDIN);
			exit(0);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status)
			return (FAILURE);
	}
	return (SUCCESS);
}
