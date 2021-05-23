/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:11:15 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/23 18:02:27 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "term.h"

static int	handle_key(int c, t_input *input, t_hist **hist)
{
	if (c == KEY_UP)
		print_next_hist(hist, input);
	else if (c == KEY_DOWN)
		print_prev_hist(hist, input);
	else if (c == BACK_SPACE)
		handle_backspace(input);
	else if (c == CTRL_D && input->x == 0)
		return (FAILURE);
	else if (ft_isprint(c) || c == '\n')
		handle_insert(input, c);
	return (SUCCESS);
}

/*
** return (1) 성공적으로 개행문자까지 읽음
** return (0) 빈 라인일 때 EOF를 만난 경우
** return (-1) malloc, read error
*/

int			get_line(char **line)
{
	int		n;
	int		c;
	t_input	*input;
	t_hist	*hist;

	if (init_termios(&input) == FAILURE)
		return (-1);
	hist = NULL;
	c = 0;
	while ((n = read(STDIN_FILENO, &c, sizeof(c))) > 0)
	{
		if (handle_key(c, input, &hist))
			return (0);
		if (c == '\n')
			break ;
		c = 0;
	}
	reset_input_mode();
	if (hist)
		hist_pop_front(&hist);
	if (n == -1)
		return (-1);
	*line = input->buf;
	return (1);
}
