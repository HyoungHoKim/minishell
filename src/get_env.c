/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 17:51:09 by seushin           #+#    #+#             */
/*   Updated: 2021/05/27 18:41:56 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_env(char *key)
{
	int		i;

	if ((i = get_env_idx(key)) != -1)
		return (g_state.env[i]);
	return (NULL);
}

int			get_env_idx(char *key)
{
	int		size;
	int		i;

	i = 0;
	while (g_state.env[i])
	{
		size = ft_strchr(g_state.env[i], '=') ?
			ft_strchr(g_state.env[i], '=') - g_state.env[i] :
			ft_strlen(g_state.env[i]);
		size = size < (int)ft_strlen(key) ? ft_strlen(key) : size;
		if (ft_strncmp(g_state.env[i], key, size) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char		*get_env_value(char *key)
{
	char	*env;
	char	*value;

	if ((env = get_env(key)))
		if ((value = ft_strchr(env, '=')))
			return (value + 1);
	return (NULL);
}

char		*get_env_key(char *env)
{
	char	*key;
	int		pos;

	pos = get_chr_pos(env, '=');
	if (pos == (int)ft_strlen(env) + 1)
		return (ft_strdup(env));
	key = ft_substr(env, 0, pos);
	return (key);
}
