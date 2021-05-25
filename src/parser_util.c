/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:48:59 by seushin           #+#    #+#             */
/*   Updated: 2021/05/25 19:54:29 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_flag(char c)
{
	if (c == ';')
		return (SEMI);
	else if (c == '<')
		return (REIN);
	else if (c == '>')
		return (REOUT);
	return (PIPE);
}
