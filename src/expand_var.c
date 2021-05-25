/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:43:09 by seushin           #+#    #+#             */
/*   Updated: 2021/05/25 18:06:25 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static int	get_var_len(char *buf)
{
	int		len;
	int		i;

	len = 0;
	i = 1;
	if (ft_isdigit(buf[i]) || is_set(buf[i], "$?"))
		return (1);
	while (buf[i] == '_' || ft_isalnum(buf[i]))
	{
		len++;
		i++;
	}
	return (len);
}

static char	*get_var(char *buf)
{
	char	*key;
	char	*value;
	int		len;

	len = get_var_len(buf);
	key = ft_substr(buf, 1, len);
	if (ft_strncmp(key, "?", 2) == 0)
		value = ft_itoa(g_state.errno);
	else if ((value = get_env_value(key)))
		value = ft_strdup(value);
	else
		value = ft_strdup("");
	free(key);
	return (value);
}

static char	**split_buf(char *buf)
{
	char	**res;
	int		sub_len;
	int		dollar_idx;
	int		backslash_idx;

	res = create_token();
	while (*buf)
	{
		sub_len = get_split_idx(buf, &backslash_idx, &dollar_idx);
		token_push_back(&res, ft_substr(buf, 0, sub_len));
		buf += sub_len;
		if (backslash_idx != -1)
		{
			token_push_back(&res, ft_substr(buf, 1, 1));
			buf += 2;
		}
		else if (dollar_idx != -1)
		{
			token_push_back(&res, get_var(buf));
			buf += get_var_len(buf) + 1;
			dollar_idx = -1;
		}
	}
	return (res);
}

char		*expand_var(char *buf)
{
	char	*res;
	char	**token;

	token = split_buf(buf);
	res = join_token(token);
	free_token(token);
	return (res);
}
