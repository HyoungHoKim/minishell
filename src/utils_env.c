/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:41:35 by seushin           #+#    #+#             */
/*   Updated: 2021/05/25 13:28:52 by hyoukim          ###   ########.fr       */
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

	size = ft_strlen(key);
	i = 0;
	while (g_state.env[i])
	{
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

int			check_invalid_key(char *key)
{
	int		idx;

	idx = -1;
	if (ft_isdigit(key[0]))
		return (FAILURE);
	while (key[++idx] != '\0')
	{
		if (!ft_isalpha(key[idx]) && key[idx] != '_' && !ft_isdigit(key[idx]))
			return (FAILURE);
	}
	return (SUCCESS);
}
