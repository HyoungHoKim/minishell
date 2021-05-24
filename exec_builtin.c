/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 16:21:16 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/23 16:24:48 by hyoukim          ###   ########.fr       */
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

void		exec_builtin(char **token)
{
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
}
