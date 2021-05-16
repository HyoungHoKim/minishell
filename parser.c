/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:58:25 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/16 17:25:09 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*ft_strncpy(char *dest, char const *src, unsigned int n)
{
	unsigned int	idx;

	idx = 0;
	while (idx < n && src[idx] != '\0')
	{
		dest[idx] = src[idx];
		idx++;
	}
	dest[idx] = '\0';
	return (dest);
}

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

void					add_token(t_cmd *cmd, char *buf, int len)
{
	char			*temp;

	if (ft_strlen(buf) == 0)
		return ;
	temp = ft_strdup(buf);
	ft_memset(buf, 0, len);
	token_push_back(&(cmd->token), temp);
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
		if (parse->quote == 0 && parse->input[i] == '\"')
			parse->quote = '\"';
		else if (parse->quote == 0 && parse->input[i] == '\'')
			parse->quote = '\'';
		else if (parse->quote == 0 && parse->input[i] == ';')
		{
			(*cmd)->flag = SEMI;
			add_token(*cmd, parse->buf, j);
			j = 0;
		}
		else if (parse->quote == 0 && parse->input[i] == '|')
		{
			(*cmd)->flag = PIPE;
			add_token(*cmd, parse->buf, j);
			j = 0;
		}
		else if (parse->quote == '\"' && parse->input[i] == '\"')
		{
			parse->quote = 0;
			add_token(*cmd, parse->buf, j);
			j = 0;
		}
		else if (parse->quote == '\'' && parse->input[i] == '\'')
		{
			parse->quote = 0;
			add_token(*cmd, parse->buf, j);
			j = 0;
		}
		else if (parse->quote == 0 && parse->input[i] == ' ')
		{
			add_token(*cmd, parse->buf, j);
			j = 0;
		}
		else{
			if (parse->quote != 0)
				parse->buf[j++] = parse->input[i];
			if (parse->quote == 0 && parse->input[i] != '\\')
				parse->buf[j++] = parse->input[i];
		}	
	}
	add_token(*cmd, parse->buf, j);
	//command_seperate(line, head);
	return (0);
}
