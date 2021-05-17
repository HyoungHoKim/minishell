/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:07:51 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/17 19:16:56 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_command(char **token)
{
	int		len;
	
	if (token[0] == NULL)
		return (SUCCESS);
	len = ft_strlen(token[0]);
	if (ft_strncmp(token[0], "echo", len) == 0)
		ft_echo(token);
	if (ft_strncmp(token[0], "pwd", len) == 0)
		ft_pwd();
	if (ft_strncmp(token[0], "env", len) == 0)
		ft_env(token);
	if (ft_strncmp(token[0], "cd", len) == 0)
		ft_cd(token);
	return (SUCCESS);
}