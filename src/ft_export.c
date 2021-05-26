/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:14:21 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/26 13:05:49 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state		g_state;

int			value_size(char *value)
{
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (value[++i] != '\0')
	{
		if (value[i] == '\\' || value[i] == '\"' || value[i] == '$')
			size++;
	}
	size += ft_strlen(value);
	return (size);
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
	size = value_size(value);
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

void		replace_env(char *token, char *key)
{
	char	**exist_env;

	exist_env = &g_state.env[get_env_idx(key)];
	free(*exist_env);
	*exist_env = ft_strdup(token);
}

void		ft_export(char **token)
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
			{
				err_msg_export(token[0], token[1], "not a valid identifier", 1);
				free(key);
				return ;
			}
			if (!(get_env(key)))
				token_push_back(&g_state.env, ft_strdup(token[idx]));
			else
				replace_env(token[idx], key);
			free(key);
		}
	}
	g_state.my_errno = SUCCESS;
}
