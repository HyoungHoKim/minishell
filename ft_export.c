/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:14:21 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/21 18:50:24 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state		g_state;

int			compare_key(char *env1, char *env2)
{
	char	*key1;
	char	*key2;
	int		ret;

	key1 = get_env_key(env1);
	key2 = get_env_key(env2);
	ret = ft_strcmp(key1, key2);
	free(key1);
	free(key2);
	return (ret);
}

char		**sort_env(void)
{
	char	**env;
	char	*temp_env;
	int		i;
	int		j;

	env = copy_envp(g_state.env);
	i = -1;
	while (env[++i] != NULL)
	{
		j = i;
		while (env[++j] != NULL)
		{
			if (compare_key(env[i], env[j]) > 0)
			{
				temp_env = env[i];
				env[i] = env[j];
				env[j] = temp_env;
			}
		}
	}
	return (env);
}

char		*add_back_slash(char *value)
{
	int		i;
	int		j;
	int		size;
	char	*ret;

	if (value == NULL)
		return (NULL);
	i = -1;
	size = 0;
	while (value[++i] != '\0')
	{
		if (value[i] == '\\' || value[i] == '\"' || value[i] == '$')
			size++;
	}
	size += ft_strlen(value);
	ret = (char *)malloc(sizeof(char) * (size + 1));
	ret[size] = '\0';
	i = 0;
	j = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '\\' || value[i] == '\"' || value[i] == '$')
			ret[j++] = '\\';
		ret[j++] = value[i++];
	}
	return (ret);
}

void		print_sort_env(void)
{
	char	**sorted_env;
	char	*key;
	char	*value;

	sorted_env = sort_env();
	while (*sorted_env != NULL)
	{
		key = get_env_key(*sorted_env);
		value = add_back_slash(get_env_value(key));
		ft_putstr_fd("declare -x ", STDIN);
		ft_putstr_fd(key, STDIN);
		if (value != NULL)
		{
			ft_putstr_fd("=\"", STDIN);
			ft_putstr_fd(value, STDIN);
			ft_putstr_fd("\"", STDIN);
		}
		ft_putstr_fd("\n", STDIN);
		free(value);
		free(key);
		sorted_env++;
	}
	return ;
}

void		replace_env(char *token, char *key)
{
	char	*value;
	char	**exist_env;

	exist_env = &g_state.env[get_env_idx(key)];
	free(*exist_env);
	*exist_env = ft_strdup(token);
}

int			ft_export(char **token)
{
	int		idx;
	char	*key;

	idx = 0;
	if (token_size(token) == 1)
		print_sort_env();
	else
	{
		while (token[++idx] != NULL)
		{
			key = get_env_key(token[idx]);
			if (check_invalid_key(key))
				return (FAILURE);
			if (!(get_env(key)))
				token_push_back(&g_state.env, ft_strdup(token[idx]));
			else
				replace_env(token[idx], key);
			free(key);
		}
	}
	return (SUCCESS);
}
