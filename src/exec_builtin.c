/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 16:21:16 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/27 15:40:39 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_builtin(char **token)
{
	if (ft_strncmp(token[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(token[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(token[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(token[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(token[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(token[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(token[0], "exit", 5) == 0)
		return (1);
	return (0);
}

void		exec_builtin(t_cmd *cmd)
{
	char	**token;
	int		fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (find_redirection(cmd))
		return ;
	token = cmd->token;
	if (ft_strncmp(token[0], "echo", 5) == 0)
		ft_echo(token);
	else if (ft_strncmp(token[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(token[0], "env", 4) == 0)
		ft_env(token);
	else if (ft_strncmp(token[0], "cd", 3) == 0)
		ft_cd(token);
	else if (ft_strncmp(token[0], "export", 7) == 0)
		ft_export(token);
	else if (ft_strncmp(token[0], "unset", 6) == 0)
		ft_unset(token);
	else if (ft_strncmp(token[0], "exit", 5) == 0)
		ft_exit(token);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
}
