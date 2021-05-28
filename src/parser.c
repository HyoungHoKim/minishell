/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:58:25 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/28 16:10:39 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static int			free_parse(t_parse *parse)
{
	if (!parse)
		return (FAILURE);
	free(parse->input);
	free(parse->buf);
	free(parse);
	return (FAILURE);
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

int					parser(char **line, t_cmd *cmd)
{
	t_parse			*parse;

	if (!(parse = init_parse(*line)))
		return (FAILURE);
	if (tokenizer(parse, cmd) == FAILURE)
		return (free_parse(parse));
	free_parse(parse);
	if (ft_strlen(*line))
		hist_push_front(&g_state.hist, *line);
	free(*line);
	*line = NULL;
	return (SUCCESS);
}
