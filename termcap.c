/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:41:26 by seushin           #+#    #+#             */
/*   Updated: 2021/05/22 19:50:02 by hari3o           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "minishell.h"
#include "term.h"

t_input		*get_input(void)
{
	static t_input	input;

	return (&input);
}

int			init_termios(t_input **input)
{
	struct termios	term;

	*input = get_input();
	if (!((*input)->buf = ft_strdup("")))
		return (FAILURE);
	(*input)->x = 0;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (SUCCESS);
}

int			show_new_line(void)
{
	t_input	*input;

	input = get_input();
	tputs(tgetstr("do", NULL), 1, ft_putchar);
	tputs(tgetstr("ll", NULL), 1, ft_putchar);
	free(input->buf);
	if (!(input->buf = ft_strdup("")))
		return (FAILURE);
	input->x = 0;
	show_prompt();
	return (SUCCESS);
}

void		reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_state.backup);
}
