/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:15:12 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/25 13:28:28 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_n_option(char *option)
{
	int		idx;

	idx = 1;
	if (option[0] == '-')
	{
		while (option[idx] != '\0')
		{
			if (option[idx++] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

void		ft_echo(char **token)
{
	int		idx;
	int		is_n;

	idx = 0;
	is_n = 0;
	if (token_size(token) == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else
	{
		while (token[++idx] != NULL)
		{
			if (check_n_option(token[idx]))
				is_n = 1;
			else
				break ;
		}
		while (token[idx] != NULL)
		{
			ft_putstr_fd(token[idx++], STDOUT_FILENO);
			if (token[idx] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		if (!is_n)
			ft_putstr_fd("\n", STDOUT_FILENO);
	}
}
