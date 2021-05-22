/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keycode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:37:44 by seushin           #+#    #+#             */
/*   Updated: 2021/05/22 20:08:32 by hari3o           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termcap.h>

static char	*delete_char(char *str)
{
	int		size;
	char	*res;

	size = ft_strlen(str);
	if (!(res = ft_calloc(sizeof(char), size)))
		return (NULL);
	ft_strlcpy(res, str, size);
	return (res);
}

static char	*insert_char(char *str, int c)
{
	int		size;
	char	*res;

	size = ft_strlen(str);
	if (!(res = ft_calloc(sizeof(char), size + 2)))
		return (NULL);
	ft_strlcpy(res, str, size + 2);
	res[size] = c;
	return (res);
}

int			handle_backspace(t_input *input)
{
	char	*tmp;

	if (input->x <= 0)
		return (SUCCESS);
	if (!(tmp = delete_char(input->buf)))
		return (FAILURE);
	free(input->buf);
	input->buf = tmp;
	(input->x)--;
	tputs(tgetstr("le", NULL), 1, ft_putchar);
	tputs(tgetstr("dm", NULL), 1, ft_putchar);
	tputs(tgetstr("dc", NULL), 1, ft_putchar);
	tputs(tgetstr("ed", NULL), 1, ft_putchar);
	return (SUCCESS);
}

int			handle_insert(t_input *input, int c)
{
	char	*tmp;

	if (c != '\n')
	{
		if (!(tmp = insert_char(input->buf, c)))
			return (FAILURE);
		free(input->buf);
		input->buf = tmp;
		(input->x)++;
	}
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	tputs(tgetstr("ic", NULL), 1, ft_putchar);
	ft_putchar(c);
	tputs(tgetstr("ip", NULL), 1, ft_putchar);
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	return (SUCCESS);
}
