/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:11:15 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/13 13:11:17 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_line(char **line)
{
	char	buf[2];
	char	*temp;

	ft_bzero(buf, 2);
	*line = ft_strdup("");
	temp = 0;
	while (*buf != '\n')
	{
		while (read(0, buf, 1) && *buf != '\n')
		{
			temp = ft_strjoin(*line, buf);
			free(*line);
			*line = temp;
		}
		if (ft_strlen(*line) == 0 && *buf != '\n')
			return (0);
	}
	return (1);
}