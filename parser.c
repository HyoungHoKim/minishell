/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:58:25 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/16 18:52:50 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse				*init_parse(char *line)
{
	char			*input;
	t_parse			*temp;
	size_t			size;

	temp = (t_parse *)malloc(sizeof(t_parse));
	input = del_side_space(line);
	size = ft_strlen(input);
	temp->input = input;
	temp->buf = (char *)malloc(sizeof(char) * (size + 1));
	ft_memset(temp->buf, 0, size + 1);
	temp->quote = 0;
	return (temp);
}

void					add_token(t_cmd *cmd, char *buf, int *len)
{
	char			*temp;

	if (ft_strlen(buf) == 0)
		return ;
	temp = expand_var(buf);
	ft_memset(buf, 0, *len);
	*len = 0;
	token_push_back(&(cmd->token), temp);
}
int					set_semi_pipe(t_cmd **cmd, char *buf, char c, int *len)
{
	add_token(*cmd, buf, len);
	if (c == ';')
		return (SEMI);
	return (PIPE);
}

void				set_non_quote(t_cmd **cmd, t_parse *parse, int i, int *j)
{
	if (parse->input[i] == '\"' || parse->input[i] == '\'')
		parse->quote = parse->input[i];
	else if (parse->input[i] == ';' || parse->input[i] == '|')
		set_semi_pipe(cmd, parse->buf, parse->input[i], j);
	else if (parse->input[i] == ' ')
		add_token(*cmd, parse->buf, j);
	else if (parse->input[i] != '\\')
		parse->buf[(*j)++] = parse->input[i];
}

int					parser(char *line, t_cmd **cmd)
{
	t_parse			*parse;
	int				i;
	int				j;
	
	*cmd = create_cmd();
	parse = init_parse(line);
	i = -1;
	j = 0;
	while (parse->input[++i] != '\0')
	{
		if (parse->quote == 0)
			set_non_quote(cmd, parse, i, &j);
		else if ((parse->quote == '\"' && parse->input[i] == '\"')
			|| (parse->quote == '\'' && parse->input[i] == '\''))
		{
			parse->quote = 0;
			add_token(*cmd, parse->buf, &j);
		}
		else if (parse->quote != 0)
			parse->buf[j++] = parse->input[i];
	}
	add_token(*cmd, parse->buf, &j);
	return (0);
}
