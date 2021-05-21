/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keycode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:37:44 by seushin           #+#    #+#             */
/*   Updated: 2021/05/21 18:38:07 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termcap.h>

void	handle_backspace(t_input *input)
{
	if (input->x <= 0)
		return ;
	(input->x)--;
	ft_memmove(input->buf + input->x - 1, input->buf + input->x,
			sizeof(input->buf));
	tputs(tgetstr("le", NULL), 1, ft_putchar);
	tputs(tgetstr("dm", NULL), 1, ft_putchar);
	tputs(tgetstr("dc", NULL), 1, ft_putchar);
	tputs(tgetstr("ed", NULL), 1, ft_putchar);
}

void	handle_move_left(t_input *input)
{
	if (input->x <= 0)
		return ;
	(input->x)--;
	tputs(tgetstr("le", NULL), 1, ft_putchar);
}

void	handle_move_right(t_input *input)
{
	if (input->buf[input->x] == 0)
		return ;
	(input->x)++;
	tputs(tgetstr("nd", NULL), 1, ft_putchar);
}

void	handle_insert(t_input *input, int c)
{
	ft_memmove(input->buf + input->x + 1, input->buf + input->x,
			sizeof(input->buf));
	input->buf[input->x] = c;
	(input->x)++;
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	tputs(tgetstr("ic", NULL), 1, ft_putchar);
	ft_putchar(c);
	tputs(tgetstr("ip", NULL), 1, ft_putchar);
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
}
