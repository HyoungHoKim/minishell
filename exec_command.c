/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:07:51 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/21 18:47:37 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_command(char **token)
{
	int		len;

	if (token[0] == NULL)
		return (SUCCESS);
	else if (ft_strncmp(token[0], "echo", 5) == 0)
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
	else
		extern_func(token);
	return (SUCCESS);
}
