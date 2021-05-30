/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 13:27:03 by seushin           #+#    #+#             */
/*   Updated: 2021/05/30 14:54:55 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_redirection_err(t_cmd *cmd, int i)
{
	if (cmd->token[i + 1] == NULL || cmd->token[i + 1][0] == 0)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline`\n",
				STDERR_FILENO);
		g_state.my_errno = 258;
	}
	else
	{
		err_msg_extern(cmd->token[i + 1], strerror(errno));
		g_state.my_errno = 1;
	}
	return (FAILURE);
}
