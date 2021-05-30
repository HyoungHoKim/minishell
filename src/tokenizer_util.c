/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 17:19:36 by seushin           #+#    #+#             */
/*   Updated: 2021/05/30 15:57:02 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				end_of_quote(t_parse *parse, t_cmd *cmd)
{
	int				dummy;

	parse->quote = 0;
	add_token(cmd, parse, &dummy);
	ft_putstr_fd("bash: syntax error near unexpected token `newline`\n",
			STDERR_FILENO);
	g_state.my_errno = 258;
	return (FAILURE);
}

static char		*join_save_token(char **save, char *token)
{
	char			*res;

	res = ft_strjoin(*save, token);
	free(*save);
	free(token);
	*save = NULL;
	return (res);
}

static char		*get_single_token(t_parse *parse)
{
	char			*res;

	if (parse->quote == '\'')
		res = ft_strdup(parse->buf);
	else
		res = expand_var(parse->buf);
	return (res);
}

void			add_token(t_cmd *cmd, t_parse *parse, int *buf_i)
{
	char			*single_token;
	char			*tmp;
	static char		*save;

	*buf_i = 0;
	if (!save && ft_strlen(parse->buf) == 0)
		return ;
	if (parse->quote)
	{
		tmp = get_single_token(parse);
		if (save)
			save = join_save_token(&save, tmp);
		else
			save = tmp;
		ft_memset(parse->buf, 0, sizeof(parse->buf));
		return ;
	}
	single_token = get_single_token(parse);
	if (save)
		single_token = join_save_token(&save, single_token);
	if (ft_strlen(single_token))
		token_push_back(&(cmd->token), single_token);
	else
		free(single_token);
	ft_memset(parse->buf, 0, sizeof(parse->buf));
}
