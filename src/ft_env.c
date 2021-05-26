/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 18:47:28 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/26 13:04:00 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_env(char **token)
{
	if (token_size(token) == 1)
	{
		print_env();
		g_state.my_errno = SUCCESS;
	}
	else
		err_msg(token[0], token[1], "too many argument", 127);
}
