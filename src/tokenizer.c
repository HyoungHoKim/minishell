/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:27:59 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/27 16:57:43 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			add_token(t_cmd *cmd, t_parse *parse, int *buf_i, int flag)
{
	char			*single_token;
	char			*tmp;
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
		tmp = ft_strjoin(save, single_token);
		free(save);
		free(single_token);
		single_token = tmp;
		save = NULL;
	}
	token_push_back(&(cmd->token), single_token);
	ft_memset(parse->buf, 0, sizeof(parse->buf));
}

static int			parse_single_char(t_cmd **cmd, t_parse *parse, int *buf_i)
{
	if (is_set(*parse->input, "\"\'"))
	{
		parse->quote = *parse->input;
		if (*buf_i != 0)
			add_token(*cmd, parse, buf_i, 1);
	}
	else if (is_set(*parse->input, ";|"))
	{
		add_token(*cmd, parse, buf_i, 0);
		(*cmd)->flag = get_flag(*parse->input);
		if (!*(*cmd)->token)
			return (FAILURE);
		*cmd = add_cmd(*cmd);
	}
	else if (*parse->input == ' ')
		add_token(*cmd, parse, buf_i, 0);
	else if (is_set(*parse->input, "<>"))
	{
		add_token(*cmd, parse, buf_i, 0);
		parse->buf[(*buf_i)++] = *parse->input;
		if (*parse->input == '>' && *(parse->input + 1) == '>')
			parse->buf[(*buf_i)++] = *parse->input++;
		add_token(*cmd, parse, buf_i, 0);
	}
	else if (*parse->input != '\\')
		parse->buf[(*buf_i)++] = *parse->input;
	return (SUCCESS);
}

static void			parse_in_quote(t_parse *parse, int *buf_i)
{
	static int		bs_flag;

	if (*buf_i == 0)
		bs_flag = 0;
	if (parse->quote == *parse->input && !bs_flag)
		parse->quote = 0;
	else
	{
		if (bs_flag)
			bs_flag = 0;
		else if (*parse->input == '\\')
			bs_flag = 1;
		parse->buf[(*buf_i)++] = *parse->input;
	}
}

int					tokenizer(t_parse *parse, t_cmd *cmd)
{
	char			*head;
	int				buf_i;
	int				err;

	buf_i = 0;
	err = 0;
	head = parse->input;
	while (*parse->input != '\0')
	{
		if (parse->quote == 0)
			err |= parse_single_char(&cmd, parse, &buf_i);
		else
			parse_in_quote(parse, &buf_i);
		parse->input++;
	}
	add_token(cmd, parse, &buf_i, 0);
	parse->input = head;
	if (parse->quote || err)
		return (FAILURE);
	return (SUCCESS);
}
