/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 19:20:42 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/25 19:23:57 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char		**sort_env(char **env)
{
	char	*temp_env;
	int		i;
	int		j;

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

void		print_env_line(char *key, char *value)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(key, STDOUT_FILENO);
	if (value != NULL)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(value);
	free(key);
}

void		print_sort_env(void)
{
	char	**env;
	char	**sorted_env;
	char	*key;
	char	*value;

	env = copy_envp(g_state.env);
	sorted_env = sort_env(env);
	while (*sorted_env != NULL)
	{
		key = get_env_key(*sorted_env);
		value = add_back_slash(get_env_value(key));
		print_env_line(key, value);
		sorted_env++;
	}
	free_token(env);
	return ;
}
