/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:22:10 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/25 13:29:14 by hyoukim          ###   ########.fr       */
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
	if (token_size(token) == 1)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	else if (token_size(token) == 2)
	{
		if (ft_isdigit_str(token[1]))
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			ft_putstr_fd("bash: exit: ", STDOUT_FILENO);
			ft_putstr_fd(token[1], STDOUT_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(ft_atoi(token[1]));
	}
	else
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("bash: exit: ", STDOUT_FILENO);
		ft_putstr_fd("too many argument\n", STDOUT_FILENO);
	}
}
