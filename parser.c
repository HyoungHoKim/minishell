/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:58:25 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/18 15:41:28 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			free_parse(t_parse *parse)
{
	if (!parse)
		return ;
	free(parse->input);
	free(parse->buf);
	free(parse);
}

static t_parse		*init_parse(char *line)
{
	t_parse			*res;
	size_t			size;

	if (!(res = ft_calloc(sizeof(t_parse), 1)))
		return (NULL);
	if (!(res->input = ft_strtrim(line, " ")))
	{
		free_parse(res);
		return (NULL);
	}
	size = ft_strlen(res->input);
	if (!(res->buf = ft_calloc(sizeof(char), size + 1)))
	{
		free_parse(res);
		return (NULL);
	}
	return (res);
}

static void			add_token(t_cmd *cmd, t_parse *parse, int *buf_i)
{
	char			*temp;

	if (ft_strlen(parse->buf) == 0)
		return ;
	if (parse->quote == '\'')
		temp = ft_strdup(parse->buf);
	else
		temp = expand_var(parse->buf);
	ft_memset(parse->buf, 0, *buf_i);
	*buf_i = 0;
	token_push_back(&(cmd->token), temp);
}

static int			set_semi_pipe(char c)
{
	if (c == ';')
		return (SEMI);
	return (PIPE);
}

static void			set_non_quote(t_cmd **cmd, t_parse *parse, int *buf_i)
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

int					parser(char *line, t_cmd *cmd)
{
	t_parse			*parse;
	char			*tmp;
	int				buf_i;

	if (!(parse = init_parse(line)))
		return (FAILURE);
	tmp = parse->input;
	buf_i = 0;
	while (*parse->input != '\0')
	{
		if (parse->quote == 0)
			set_non_quote(&cmd, parse, &buf_i);
		else if ((parse->quote == *parse->input && *(parse->input - 1) != '\\'))
		{
			add_token(cmd, parse, &buf_i);
			parse->quote = 0;
		}
		else
			parse->buf[buf_i++] = *parse->input;
		parse->input++;
	}
	add_token(cmd, parse, &buf_i);
	parse->input = tmp;
	free_parse(parse);
	return (SUCCESS);
}
