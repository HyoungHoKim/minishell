/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:11:15 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/18 18:20:48 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>

static int	handle_signal_in_gnl(char **line)
{
	// TODO: EOF를 받더라도 커서를 이동할 수 있게 변경
	if (ft_strlen(*line) == 0)
		return (1);
	ft_putstr_fd("  \b\b\n", STDOUT_FILENO);
	return (0);
}

/*
** return (1) 성공적으로 개행문자까지 읽음
** return (0) 빈 라인일 때 EOF를 만난 경우
** return (-1) malloc, read error
**
*/
int			get_line(char **line)
{
	char	buf[2];
	char	*temp;
	int		n;

	if (!*line && !(*line = ft_strdup("")))
		return (-1);
	ft_bzero(buf, 2);
	while ((n = read(STDIN_FILENO, buf, 1)) > 0 && *buf != '\n')
	{
		temp = ft_strjoin(*line, buf);
		free(*line);
		*line = temp;
		if (!temp)
			return (-1);
	}
	if (n == -1)
		return (-1);
	else if (n == 0 && handle_signal_in_gnl(line))
		return (0);
	return (1);
}
