/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:07:51 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/16 21:30:05 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_command(t_cmd *cmd)
{
	char	*command;
	int		len;

	command = cmd->token[0];
	len = ft_strlen(command);
	if (ft_strncmp(command, "echo", len) == 0)
		ft_echo(cmd);
}