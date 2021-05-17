/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:15:12 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/17 14:42:09 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_echo(char **token)
{
	int     idx;

    idx = 0;
    while (token[++idx] != NULL)
        ft_putstr_fd(token[idx], STDIN);
    ft_putstr_fd("\n", STDIN);
}