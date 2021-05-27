/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:41:35 by seushin           #+#    #+#             */
/*   Updated: 2021/05/27 18:57:12 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**copy_envp(char **envp)
{
	char	**res;
	int		i;

	if (!(res = create_token()))
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (token_push_back(&res, ft_strdup(envp[i])) == FAILURE)
		{
			free_token(res);
			return (NULL);
		}
		i++;
	}
	return (res);
}

void		print_env(void)
{
	int		idx;
	char	*key;
	char	*value;

	idx = -1;
	while (g_state.env[++idx] != NULL)
	{
		key = get_env_key(g_state.env[idx]);
		value = get_env_value(key);
		if (value != NULL)
		{
			ft_putstr_fd(g_state.env[idx], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		free(key);
	}
}

int			check_invalid_key(char *key)
{
	int		idx;

	idx = -1;
	if (ft_isdigit(key[0]) || key[0] == '\0')
		return (FAILURE);
	while (key[++idx] != '\0')
	{
		if (!ft_isalpha(key[idx]) && key[idx] != '_' && !ft_isdigit(key[idx]))
			return (FAILURE);
	}
	return (SUCCESS);
}
