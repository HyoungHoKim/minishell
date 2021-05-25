/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:06:47 by seushin           #+#    #+#             */
/*   Updated: 2021/05/25 15:08:26 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_total_len(char **token)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (token[i])
	{
		len += ft_strlen(token[i]);
		i++;
	}
	return (len);
}

char		*join_token(char **token)
{
	char	*res;
	int		len;
	int		i;

	len = get_total_len(token);
	if (!(res = ft_calloc(sizeof(char), len + 1)))
		return (NULL);
	i = -1;
	while (token[++i])
		ft_strlcat(res, token[i], len + 1);
	return (res);
}
