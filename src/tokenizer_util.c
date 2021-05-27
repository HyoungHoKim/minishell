/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 17:19:36 by seushin           #+#    #+#             */
/*   Updated: 2021/05/27 17:36:30 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*join_save_token(char *save, char *token)
{
	char			*res;

	res = ft_strjoin(save, token);
	free(save);
	free(token);
	return (res);
}

void			add_token(t_cmd *cmd, t_parse *parse, int *buf_i, int flag)
{
	char			*single_token;
	static char		*save;

	*buf_i = 0;
	if (ft_strlen(parse->buf) == 0)
		return ;
	if (flag)
	{
		save = expand_var(parse->buf);
		ft_memset(parse->buf, 0, sizeof(parse->buf));
		return ;
	}
	if (parse->quote == '\'')
		single_token = ft_strdup(parse->buf);
	else
		single_token = expand_var(parse->buf);
	if (save)
	{
		single_token = join_save_token(save, single_token);
		save = NULL;
	}
	if (ft_strlen(single_token))
		token_push_back(&(cmd->token), single_token);
	else
		free(single_token);
	ft_memset(parse->buf, 0, sizeof(parse->buf));
}
