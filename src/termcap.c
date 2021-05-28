/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:41:26 by seushin           #+#    #+#             */
/*   Updated: 2021/05/28 22:55:15 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "term.h"

t_input		*get_input(void)
{
	static t_input	input;

	return (&input);
}

static int	init_input(t_input **input)
{
	*input = get_input();
	if (!((*input)->buf = ft_strdup("")))
		return (FAILURE);
	(*input)->x = 0;
	return (SUCCESS);
}

int			init_termios(t_input **input)
{
	struct termios	term;

	if (init_input(input) == FAILURE)
		return (FAILURE);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (SUCCESS);
}

void		reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_state.backup);
}
