/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:38:24 by seushin           #+#    #+#             */
/*   Updated: 2021/05/27 18:10:38 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

t_cmd		*create_cmd(void)
{
	t_cmd	*res;
	
	res = ft_calloc(sizeof(t_cmd), 1);
	if (!res)
		return (NULL);
	res->token = create_token();
	if (!res->token)
	{
		free(res);
		res = NULL;
	}
	res->prev = NULL;
	res->next = NULL;
	return (res);
}

t_cmd		*rewind_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (cmd);
	while (cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}

t_cmd		*add_cmd(t_cmd *cur)
{
	t_cmd	*new;

	if (!(new = create_cmd()))
		return (NULL);
	cur->next = new;
	new->prev = cur;
	return (new);
}

void		free_cmd(t_cmd *cmd)
{
	t_cmd	*prev;

	while (cmd)
	{
		free_token(cmd->token);
		cmd->prev = NULL;
		prev = cmd;
		cmd = cmd->next;
		free(prev);
		prev = NULL;
	}
}

int			cmd_size(t_cmd *cmd)
{
	int cnt;

	cnt = 0;
	while (cmd != NULL)
	{
		cnt++;
		cmd = cmd->next;
	}
	return (cnt);
}
