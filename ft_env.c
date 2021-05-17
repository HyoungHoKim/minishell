/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 18:47:28 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/17 19:34:56 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state		g_state;

void		print_env(void)
{
	int		idx;

	idx = -1;
	while (g_state.env[++idx] != NULL)
	{
		ft_putstr_fd(g_state.env[idx], STDIN);
		ft_putstr_fd("\n", STDIN);
	}
}

void		ft_env(char **token)
{
	if (token_size(token) == 1)
		print_env();
	//else
	// 에러처리??
}