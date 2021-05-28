/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:42:58 by seushin           #+#    #+#             */
/*   Updated: 2021/05/23 17:53:44 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char		**create_token(void)
{
	char	**res;

	res = (char **)malloc(sizeof(char *));
	if (res)
		*res = NULL;
	return (res);
}

int			token_size(char **token)
{
	int		i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}

int			token_push_back(char ***token, char *str)
{
	char	**res;
	int		prev_size;
	int		i;

	prev_size = token_size(*token);
	res = (char **)malloc(sizeof(char *) * (prev_size + 2));
	if (!res)
		return (FAILURE);
	i = 0;
	while (i < prev_size)
	{
		res[i] = (*token)[i];
		i++;
	}
	res[i++] = str;
	res[i] = NULL;
	free(*token);
	*token = res;
	return (SUCCESS);
}

void		free_token(char **token)
{
	int		i;

	i = 0;
	while (token && token[i])
		free(token[i++]);
	free(token);
}
