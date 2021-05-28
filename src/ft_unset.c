/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:55:04 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/28 22:43:21 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		env_delete(int del_idx)
{
	char	**new_env;
	int		idx;

	idx = -1;
	new_env = create_token();
	while (g_state.env[++idx] != NULL)
	{
		if (idx != del_idx)
			token_push_back(&new_env, ft_strdup(g_state.env[idx]));
	}
	free_token(g_state.env);
	g_state.env = new_env;
}

void		ft_unset(char **token)
{
	int		idx;
	char	*key;
	int		del_idx;

	idx = 0;
	while (token[++idx] != NULL)
	{
		key = get_env_key(token[idx]);
		if (check_invalid_key(key))
			break ;
		if ((del_idx = get_env_idx(key)) != -1)
			env_delete(del_idx);
		free(key);
	}
	g_state.my_errno = SUCCESS;
}
