/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:17:59 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/28 15:21:59 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_extern(t_cmd *cmd)
{
	int		ret;
	char	*path;
	
	if (cmd->flag == 1 || cmd->flag == 0)
		if ((path = find_extern_dir(cmd->token[0])) == NULL)
		{
			err_msg_extern(cmd->token[0], "command not found");
			exit(g_state.my_errno);
		}
	ret = execve(path, cmd->token, g_state.env);
	return (ret);
}