/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:27:59 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/25 20:02:23 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			add_token(t_cmd *cmd, t_parse *parse, int *buf_i)
{
	char			*single_token;

	*buf_i = 0;
	if (ft_strlen(parse->buf) == 0)
		return ;
	if (parse->quote == '\'')
		single_token = ft_strdup(parse->buf);
	else
		single_token = expand_var(parse->buf);
	if (token_size(cmd->token) &&
			cmd->prev && (cmd->prev->flag == REIN || cmd->prev->flag == REOUT))
		token_push_back(&(cmd->prev->token), single_token);
	else
		token_push_back(&(cmd->token), single_token);
	ft_memset(parse->buf, 0, sizeof(parse->buf));
}

static int			parse_single_char(t_cmd **cmd, t_parse *parse, int *buf_i)
{
	if (is_set(*parse->input, "\"\'"))
		parse->quote = *parse->input;
	else if (is_set(*parse->input, ";|<>"))
	{
		add_token(*cmd, parse, buf_i);
		(*cmd)->flag = get_flag(*parse->input);
		if (!*(*cmd)->token)
			return (FAILURE);
		*cmd = add_cmd(*cmd);
	}
	else if (*parse->input == ' ')
		add_token(*cmd, parse, buf_i);
	else if (*parse->input != '\\')
		parse->buf[(*buf_i)++] = *parse->input;
	return (SUCCESS);
}

static void			parse_in_quote(t_parse *parse, t_cmd *cmd, int *buf_i)
{
	static int		bs_flag;

	if (*buf_i == 0)
		bs_flag = 0;
	if (parse->quote == *parse->input && !bs_flag)
	{
		add_token(cmd, parse, buf_i);
		parse->quote = 0;
	}
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
			parse_in_quote(parse, cmd, &buf_i);
		parse->input++;
	}
	add_token(cmd, parse, &buf_i);
	parse->input = head;
	if (parse->quote || err)
		return (FAILURE);
	return (SUCCESS);
}
