/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:22:10 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/26 13:07:26 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_isdigit_str(char *token)
{
	int		idx;

	idx = -1;
	while (token[++idx] != '\0')
	{
		if (!ft_isdigit(token[idx]))
			return (FAILURE);
	}
	return (SUCCESS);
}

void		ft_exit(char **token)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (token_size(token) == 1)
	{
		g_state.my_errno = SUCCESS;
		exit(EXIT_SUCCESS);
	}
	else if (token_size(token) == 2)
	{
		if (ft_isdigit_str(token[1]))
		{
			g_state.my_errno = 255;
			err_msg(token[0], token[1], "numeric argument required", 255);
			exit(255);
		}
		g_state.my_errno = ft_atoi(token[1]);
		exit(g_state.my_errno);
	}
	else
	{
		g_state.my_errno = 1;
		err_msg(token[0], token[1], "too many argument", 1);
	}
}
