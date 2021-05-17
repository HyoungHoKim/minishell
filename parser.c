/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:58:25 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/17 14:37:55 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse				*init_parse(char *line)
{
	t_parse			*res;
	char			*input;
	size_t			size;

	res = ft_calloc(sizeof(t_parse), 1);
	input = del_side_space(line);
	res->input = input;
	size = ft_strlen(input);
	res->buf = ft_calloc(sizeof(char), size + 1);
	return (res);
}

void				add_token(t_cmd *cmd, t_parse *parse, int *buf_i)
{
	char			*temp;

	if (ft_strlen(parse->buf) == 0)
		return ;
	if (parse->quote == '\"')
		temp = expand_var(parse->buf);
	else
		temp = ft_strdup(parse->buf);
	ft_memset(parse->buf, 0, *buf_i);
	*buf_i = 0;
	token_push_back(&(cmd->token), temp);
}

int					set_semi_pipe(char c)
{
	if (c == ';')
		return (SEMI);
	return (PIPE);
}

void				set_non_quote(t_cmd **cmd, t_parse *parse, int *buf_i)
{
	if (*parse->input == '\"' || *parse->input == '\'')
		parse->quote = *parse->input;
	else if (*parse->input == ';' || *parse->input == '|')
	{
		add_token(*cmd, parse, buf_i);
		(*cmd)->flag = set_semi_pipe(*parse->input);
		*cmd = add_cmd(*cmd);
	}
	else if (*parse->input == ' ')
		add_token(*cmd, parse, buf_i);
	else if (*parse->input != '\\')
		parse->buf[(*buf_i)++] = *parse->input;
}

int					parser(char *line, t_cmd **cmd)
{
	t_parse			*parse;
	int				buf_i;

	*cmd = create_cmd();
	parse = init_parse(line);
	buf_i = 0;
	while (*parse->input != '\0')
	{
		if (parse->quote == 0)
			set_non_quote(cmd, parse, &buf_i);
		else if ((parse->quote == *parse->input && *(parse->input - 1) != '\\'))
		{
			add_token(*cmd, parse, &buf_i);
			parse->quote = 0;
		}
		else
			parse->buf[buf_i++] = *parse->input;
		parse->input++;
	}
	add_token(*cmd, parse, &buf_i);
	return (0);
}
