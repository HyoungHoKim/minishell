/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:44:14 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/25 16:30:00 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_command(t_cmd *cmd)
{
	if (check_builtin(cmd->token) && cmd->flag == 0)
		exec_builtin(cmd->token);
	else
		exec_pipe(cmd);
}