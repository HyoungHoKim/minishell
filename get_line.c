/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:11:15 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/21 18:30:43 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>

static int	handle_key(t_input *input, int c)
{
	if (c == LEFT_ARW)
		handle_move_left(input);
	else if (c == RIGHT_ARW)
		handle_move_right(input);
	else if (c == BACK_SPACE)
		handle_backspace(input);
	else if (c == CTRL_D && input->x == 0)
		return (FAILURE);
	else if (ft_isprint(c))
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

	input = get_input();
	ft_memset(input, 0, sizeof(t_input));
	if (init_term(input))
		return (FAILURE);
	while ((n = read(STDIN_FILENO, &c, sizeof(c))) > 0)
	{
		if (c == '\n')
			break;
		if (handle_key(input, c))
			return (0);
		c = 0;
	}
	ft_putchar('\n');
	reset_input_mode(input);
	if (n == -1)
		return (-1);
	*line = ft_strdup(input->buf);
	return (1);
}
